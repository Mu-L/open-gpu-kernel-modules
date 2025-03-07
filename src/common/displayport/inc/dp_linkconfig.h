/*
 * SPDX-FileCopyrightText: Copyright (c) 2010-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/******************************* List **************************************\
*                                                                           *
* Module: dp_linkconfig.h                                                   *
*   Link Configuration object implementation                                *
*                                                                           *
\***************************************************************************/
#ifndef INCLUDED_DP_LINKCONFIG_H
#define INCLUDED_DP_LINKCONFIG_H

#include "dp_auxdefs.h"
#include "dp_internal.h"
#include "dp_watermark.h"
#include "ctrl/ctrl0073/ctrl0073specific.h" // NV0073_CTRL_HDCP_VPRIME_SIZE
#include "displayport.h"

#include "displayport2x.h"
#define NV_SUPPORTED_DP_LINK_RATES__SIZE NV_SUPPORTED_DP2X_LINK_RATES__SIZE
extern NvU32 bSupportInternalUhbrOnFpga;
namespace DisplayPort
{
    typedef NvU64 LinkRate;

    class LinkRates : virtual public Object
    {
    public:
        NvU8 entries;
        // Store link rate in multipler of 10MBPS to save space
        NvU16 element[NV_SUPPORTED_DP_LINK_RATES__SIZE];

        LinkRates()
        {
            entries = 0;
            for (int i = 0; i < NV_SUPPORTED_DP_LINK_RATES__SIZE; i++)
            {
                element[i] = 0;
            }
        }

        void clear()
        {
            entries = 0;
            for (int i = 0; i < NV_SUPPORTED_DP_LINK_RATES__SIZE; i++)
            {
                element[i] = 0;
            }
        }

        // Only use import if element can be added at the end
        // given element list needs to be sorted
        bool import(NvU16 linkBw)
        {
            if (!IS_VALID_DP2_X_LINKBW(linkBw))
            {
                DP_ASSERT(0 && "Unsupported Link Bandwidth");
                return false;
            }

            if (entries < NV_SUPPORTED_DP_LINK_RATES__SIZE)
            {
                element[entries] = linkBw;
                entries++;
                return true;
            }
            else
                return false;
        }

        // Use insert to import to the right spot in the sorted
        // element list if you are not sure of where linkBw is compared
        // to existing entries in the element list
        bool insert(NvU16 linkBw)
        {
            if (!IS_VALID_DP2_X_LINKBW(linkBw))
            {
                DP_ASSERT(0 && "Unsupported Link Bandwidth");
                return false;
            }

            for (int i = 0; i < entries; i++)
            {
                if (element[i] == linkBw)
                {
                    // element already present, nothing to do here
                    return true;
                }
                else if (element[i] > linkBw)
                {
                    // make space for the new element
                    if (entries >= NV_SUPPORTED_DP_LINK_RATES__SIZE) {
                        DP_ASSERT(0 && "No more space for adding additional link rate");
                        return false;
                    }

                    for (int j = entries-1; j >= i; j--)
                    {
                        element[j+1] = element[j];
                    }
                    entries++;
                    // space is made, insert linkBw to the right spot
                    element[i] = linkBw;
                    return true;
                }

            }
            // if we are here and not returned, that means linkBw is bigger than
            // the current entries, just import
            return import(linkBw);
        }

        LinkRate getLowerRate(LinkRate rate)
        {
            int i;

            if ((entries == 0) || (rate <= element[0]))
                return 0;

            for (i = entries - 1; i > 0; i--)
            {
                if (rate > element[i])
                    break;
            }

            return ((LinkRate)element[i]);
        }

        LinkRate getMaxRate()
        {
            LinkRate rate = 0;
            if ((entries > 0) &&
                (entries <= NV_SUPPORTED_DP_LINK_RATES__SIZE))
            {
                rate = (LinkRate)element[entries - 1];
            }
            return rate;
        }

        NvU8 getNumElements()
        {
            return NV_SUPPORTED_DP_LINK_RATES__SIZE;
        }

        NvU8 getNumLinkRates()
        {
            return entries;
        }
    };
    class LinkPolicy : virtual public Object
    {
    protected:
        bool            bNoFallback;                // No fallback when LT fails
        LinkRates       linkRates;

    public:
        LinkPolicy() : bNoFallback(false)
        {
        }
        bool skipFallback()
        {
            return bNoFallback;
        }
        void setSkipFallBack(bool bSkipFallback)
        {
            bNoFallback = bSkipFallback;
        }

        LinkRates *getLinkRates()
        {
            return &linkRates;
        }
    };

    enum
    {
        totalTimeslots = 64,
        totalUsableTimeslots = totalTimeslots - 1
    };

    //
    // Link Data Rate per DP Lane, in MBPS,
    // For 8b/10b channel coding:
    //     Link Data Rate = link rate * (8 / 10) / 8
    //                    = link rate * 0.1
    // For 128b/132b channel coding:
    //     Link Data Rate = link rate * (128 / 132) / 8
    //                    = link rate * 4 / 33
    //                   ~= link rate * 0.12
    //
    // Link Bandwidth     = Lane Count * Link Data Rate
    //
    enum
    {
        RBR             =  162000000,
        EDP_2_16GHZ     =  216000000,
        EDP_2_43GHZ     =  243000000,
        HBR             =  270000000,
        EDP_3_24GHZ     =  324000000,
        EDP_4_32GHZ     =  432000000,
        HBR2            =  540000000,
        EDP_6_75GHZ     =  675000000,
        HBR3            =  810000000,
        UHBR_2_50GHZ    =  303030303, //  2.5G * (128 / 132) / 8
        UHBR_2_70GHZ    =  327272727, //  2.7G * (128 / 132) / 8
        UHBR_5_00GHZ    =  606060606, //  5.0G * (128 / 132) / 8
        UHBR_10_0GHZ    = 1212121212, // 10.0G * (128 / 132) / 8
        UHBR_13_5GHZ    = 1636363636, // 13.5G * (128 / 132) / 8
        UHBR_20_0GHZ    = 2424242424  // 20.0G * (128 / 132) / 8
    };

    struct HDCPState
    {
        bool HDCP_State_Encryption;
        bool HDCP_State_1X_Capable;
        bool HDCP_State_22_Capable;
        bool HDCP_State_Authenticated;
        bool HDCP_State_Repeater_Capable;
    };

    struct HDCPValidateData
    {
    };

    typedef enum
    {
        DP_SINGLE_HEAD_MULTI_STREAM_MODE_NONE,
        DP_SINGLE_HEAD_MULTI_STREAM_MODE_SST,
        DP_SINGLE_HEAD_MULTI_STREAM_MODE_MST,
    }DP_SINGLE_HEAD_MULTI_STREAM_MODE;

#define HEAD_INVALID_STREAMS 0
#define HEAD_DEFAULT_STREAMS 1

    typedef enum
    {
        DP_SINGLE_HEAD_MULTI_STREAM_PIPELINE_ID_PRIMARY     = 0,
        DP_SINGLE_HEAD_MULTI_STREAM_PIPELINE_ID_SECONDARY   = 1,
        DP_SINGLE_HEAD_MULTI_STREAM_PIPELINE_ID_MAX         = DP_SINGLE_HEAD_MULTI_STREAM_PIPELINE_ID_SECONDARY,
    } DP_SINGLE_HEAD_MULTI_STREAM_PIPELINE_ID;

#define DP_INVALID_SOR_INDEX 0xFFFFFFFF
#define DSC_DEPTH_FACTOR     16

    class LinkConfiguration : virtual public Object
    {
    public:
        LinkPolicy policy;
        unsigned lanes;
        LinkRate peakRatePossible;
        LinkRate peakRate;
        LinkRate minRate;
        bool     enhancedFraming;
        bool     multistream;
        bool     disablePostLTRequest;
        bool     bEnableFEC;
        bool     bDisableLTTPR;
        bool     bDisableDownspread;
        bool     bIs128b132bChannelCoding;
        //
        // The counter to record how many times link training happens.
        // Client can reset the counter by calling setLTCounter(0)
        //
        unsigned linkTrainCounter;

        LinkConfiguration() :
            lanes(0), peakRatePossible(0), peakRate(0), minRate(0),
            enhancedFraming(false), multistream(false), disablePostLTRequest(false),
            bEnableFEC(false), bDisableLTTPR(false), bDisableDownspread(false),
            bIs128b132bChannelCoding(false),
            linkTrainCounter(0) {};

        LinkConfiguration(LinkPolicy * p, unsigned lanes, LinkRate peakRate,
                          bool enhancedFraming, bool MST,
                          bool disablePostLTRequest = false,
                          bool bEnableFEC = false,
                          bool bDisableLTTPR = false,
                          bool bDisableDownspread = false);

        void setLTCounter(unsigned counter)
        {
            linkTrainCounter = counter;
        }

        unsigned getLTCounter()
        {
            return linkTrainCounter;
        }

        // Returns data rate in Bytes per second
        NvU64 convertLinkRateToDataRate(LinkRate linkRate) const
        {
            NvU64 dataRate;
            if (bIs128b132bChannelCoding)
            {
                dataRate = LINK_RATE_TO_DATA_RATE_128B_132B(linkRate);
            }
            else
            {
                dataRate = LINK_RATE_TO_DATA_RATE_8B_10B(linkRate);
            }
            return dataRate;
        }

        // Returns minRate in data rate in Bytes per second
        NvU64 convertMinRateToDataRate() const
        {
            NvU64 dataRate;
            if (bIs128b132bChannelCoding)
            {
                dataRate = DP_LINK_RATE_BITSPS_TO_BYTESPS(DATA_BW_EFF_128B_132B(minRate));
            }
            else
            {
                dataRate = DP_LINK_RATE_BITSPS_TO_BYTESPS(OVERHEAD_8B_10B(minRate));
            }
            return dataRate;
        }

        NvU64 getTotalDataRate() const
        {
            return (convertLinkRateToDataRate(peakRate) * lanes);
        }

        NvU64 linkOverhead(NvU64 rate10M)
        {
            NvU64 rate;
            if(IS_VALID_DP2_X_LINKBW(rate10M))
            {
                // Converting here so that minRate from 10M is converted to bps
                rate = DP_LINK_RATE_10M_TO_BPS(rate10M);
            }
            else
            {
                // Convert from data rate to bps
                rate = DATA_RATE_8B_10B_TO_LINK_RATE_BPS(rate10M);
            }

            if(IS_DP2_X_UHBR_LINKBW(rate10M))
            {
                // Consider downspread only. FEC is already considered
                // in 128b/132b channel encoding
                return rate - 6 * rate/ 1000;
            }
            if(bEnableFEC)
            {
                // if FEC is enabled, we have to account for 3% overhead
                // for FEC+downspread according to DP 1.4 spec

                return rate - 3 * rate/ 100;
            }
            else
            {
                // if FEC is not enabled, link overhead comprises only of
                // 0.6% downspread.
                return rate - 6 * rate/ 1000;
            }
        }

        void enableFEC(bool setFEC)
        {
            bEnableFEC = setFEC;
            // If FEC is enabled, update minRate with FEC+downspread overhead.
            minRate = linkOverhead(peakRate);
        }

        LinkConfiguration(unsigned long TotalLinkPBN)
            : enhancedFraming(true),
              multistream(true),
              disablePostLTRequest(false),
              bEnableFEC(false),
              bDisableLTTPR(false),
              bDisableDownspread(false),
              bIs128b132bChannelCoding(false),
              linkTrainCounter(0)
        {
            //
            // Reverse engineer a link configuration from Total TotalLinkPBN
            // Note that HBR2 twice HBR. The table below treats HBR2x1 and HBRx2, etc.
            //
            // PBN Calculation
            // Definition of PBN is "54/64 MBps".
            // Note this is the "data" actually transmitted in the main link.
            // So we need to take channel coding into consideration.
            // Formula: PBN = Lane Count * Link Rate (Gbps) * 1000 * (1/8) * ChannelCoding Efficiency * (64 / 54)
            // Example:
            // 1. 4 * HBR2:    4 * 5.4 * 1000 * (1/8) * (8/10) * (64/54) = 2560
            // 2. 2 * UHBR10:  2 * 10 * 1000 * (1/8) * (128/132) * (64/54) = 2873
            //
            // Full list:
            //
            //   BW (Gbps)        Lanes              TotalLinkPBN
            //     1.62             1                     192
            //     1.62             2                     384
            //     1.62             4                     768
            //     2.70             1                     320
            //     2.70             2                     640
            //     2.70             4                    1280
            //     5.40             1                     640
            //     5.40             2                    1280
            //     5.40             4                    2560
            //     8.10             1                     960
            //     8.10             2                    1920
            //     8.10             4                    3840
            //    10.00             1                    1436
            //    10.00             2                    2873
            //    10.00             4                    5746
            //    13.50             1                    1939
            //    13.50             2                    3878
            //    13.50             4                    7757
            //    20.00             1                    2873
            //    20.00             2                    5746
            //    20.00             4                   11492
            //

            if (TotalLinkPBN <= 90)
            {
                peakRatePossible = dp2LinkRate_1_62Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_1_62Gbps);
                lanes = 0; // FAIL
            }
            if (TotalLinkPBN <= 192)
            {
                peakRatePossible = dp2LinkRate_1_62Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_1_62Gbps);
                lanes = 1;
            }
            else if (TotalLinkPBN <= 320)
            {
                peakRatePossible = dp2LinkRate_2_70Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_2_70Gbps);
                lanes = 1;
            }
            else if (TotalLinkPBN <= 384)
            {
                peakRatePossible = dp2LinkRate_1_62Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_1_62Gbps);
                lanes = 2;
            }
            else if (TotalLinkPBN <= 640)
            {
                // could be HBR2 x 1, but TotalLinkPBN works out same
                peakRatePossible = dp2LinkRate_2_70Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_2_70Gbps);
                lanes = 2;
            }
            else if (TotalLinkPBN <= 768)
            {
                peakRatePossible = dp2LinkRate_1_62Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_1_62Gbps);
                lanes = 4;
            }
            else if (TotalLinkPBN <= 960)
            {
                peakRatePossible = dp2LinkRate_8_10Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_8_10Gbps);
                lanes = 1;
            }
            else if (TotalLinkPBN <= 1280)
            {
                // could be HBR2 x 2
                peakRatePossible = dp2LinkRate_2_70Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_2_70Gbps);
                lanes = 4;
            }
            else if (TotalLinkPBN <= 1920)
            {
                peakRatePossible = dp2LinkRate_8_10Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_8_10Gbps);
                lanes = 2;
            }
            else if (TotalLinkPBN <= 2560)
            {
                peakRatePossible = dp2LinkRate_5_40Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_5_40Gbps);
                lanes = 4;
            }
            else if (TotalLinkPBN <= 3840)
            {
                peakRatePossible = dp2LinkRate_8_10Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_8_10Gbps);
                lanes = 4;
            }
            else if (TotalLinkPBN <= 3878)
            {
                peakRatePossible = dp2LinkRate_13_5Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_13_5Gbps);
                lanes = 2;
                bEnableFEC = true;
                bIs128b132bChannelCoding = true;
            }
            else if (TotalLinkPBN <= 5746)
            {
                peakRatePossible = dp2LinkRate_10_0Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_10_0Gbps);
                lanes = 4;
                bEnableFEC = true;
                bIs128b132bChannelCoding = true;
            }
            else if (TotalLinkPBN <= 7757)
            {
                peakRatePossible = dp2LinkRate_13_5Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_13_5Gbps);
                lanes = 4;
                bEnableFEC = true;
                bIs128b132bChannelCoding = true;
            }
            else if (TotalLinkPBN <= 11492)
            {
                peakRatePossible = dp2LinkRate_20_0Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_20_0Gbps);
                lanes = 4;
                bEnableFEC = true;
                bIs128b132bChannelCoding = true;
            }
            else
            {
                peakRatePossible = dp2LinkRate_1_62Gbps;
                peakRate = peakRatePossible;
                minRate = linkOverhead(dp2LinkRate_1_62Gbps);
                lanes = 0; // FAIL
                DP_ASSERT(0 && "Unknown configuration");
            }
        }

        void setEnhancedFraming(bool newEnhancedFraming)
        {
            enhancedFraming = newEnhancedFraming;
        }

        bool isValid()
        {
            return lanes != laneCount_0;
        }

        bool lowerConfig(bool bReduceLaneCnt = false);

        void setChannelCoding();

        void setChannelCoding(bool bIs128b132bChannelCoding)
        {
            this->bIs128b132bChannelCoding = bIs128b132bChannelCoding;
        }

        void setLaneRate(LinkRate newRate, unsigned newLanes)
        {
            peakRate  = newRate;
            lanes = newLanes;
            minRate = linkOverhead(peakRate);
            setChannelCoding();
        }

        unsigned pbnTotal()
        {
            return PBNForSlots(totalUsableTimeslots);
        }

        NvU64 getBytesPerTimeslot();

        void pbnRequired(const ModesetInfo & modesetInfo, unsigned & base_pbn, unsigned & slots, unsigned & slots_pbn);

        NvU32 slotsForPBN(NvU32 allocatedPBN, bool usable = false);

        NvU32 PBNForSlots(NvU32 slots);

        bool operator!= (const LinkConfiguration & right) const
        {
            return !(*this == right);
        }

        bool operator== (const LinkConfiguration & right) const
        {
            return (this->lanes == right.lanes &&
                    this->peakRate == right.peakRate &&
                    this->enhancedFraming == right.enhancedFraming &&
                    this->multistream == right.multistream &&
                    this->bEnableFEC == right.bEnableFEC);
        }

        bool operator< (const LinkConfiguration & right) const
        {
            NvU64 leftMKBps = getTotalDataRate();
            NvU64 rightMKBps = right.getTotalDataRate();

            if (leftMKBps == rightMKBps)
            {
                return (lanes < right.lanes);
            }
            else
            {
                return (leftMKBps < rightMKBps);
            }
        }
    };

#define IS_DP2X_UHBR_LINK_DATA_RATE(val)   (((NvU32)(val) == dp2LinkRate_2_50Gbps) || \
                                            ((NvU32)(val) == dp2LinkRate_2_70Gbps && bSupportInternalUhbrOnFpga) || \
                                            ((NvU32)(val) == dp2LinkRate_5_00Gbps) || \
                                            ((NvU32)(val) == dp2LinkRate_10_0Gbps) || \
                                            ((NvU32)(val) == dp2LinkRate_13_5Gbps) || \
                                            ((NvU32)(val) == dp2LinkRate_20_0Gbps))
}
#endif //INCLUDED_DP_LINKCONFIG_H
