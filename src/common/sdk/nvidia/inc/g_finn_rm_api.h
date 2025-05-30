#pragma once

//
// This file was generated with FINN, an NVIDIA coding tool.
//


#include <nvtypes.h>


#include <nvstatus.h>
#include <nvcfg_sdk.h>

#define FINN_INTERFACE_ID(T) (T ## _INTERFACE_ID)
#define FINN_MESSAGE_ID(T) (T ## _MESSAGE_ID)

#if (defined(__cplusplus) && __cplusplus >= 201103L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)
#define FINN_OFFSETOF(T,f) (offsetof(T, f))
#else
#define FINN_OFFSETOF(T,f) ((NvU64)&((T*)0)->f)
#endif

#if !defined(_MSC_VER) && (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) && !defined(__arm)
#define FINN_PACK_COMPOSITE(b) b __attribute__ ((packed))
#else
#define FINN_PACK_COMPOSITE(b) b
#endif

/*
 * FINN serialization version. A version mismatch indicates incompatibility
 * between the serializer and the deserializer.
 *
 * WARNING: Current serialization version is 0. This is a pre-release version of
 * serialization and is only intended to be used in a driver and client compiled
 * together. DO NOT use this in firmware or versioned clients.
 */
#define FINN_SERIALIZATION_VERSION 0

/*
 * FINN compiler version
 */
#define FINN_VERSION_MAJOR 1
#define FINN_VERSION_MINOR 22
#define FINN_VERSION_PATCH 0

typedef struct FINN_RM_API
{
    NV_DECLARE_ALIGNED(NvU64 version, 8);
    NV_DECLARE_ALIGNED(NvU64 payloadSize, 8);
    NV_DECLARE_ALIGNED(NvU64 interface, 8);
    NV_DECLARE_ALIGNED(NvU64 message, 8);
} FINN_RM_API;




/*!
 * @brief Private functions not to be called directly
 */
/**@{*/
NV_STATUS finnSerializeInternal_FINN_RM_API(NvU64 interface, NvU64 message, const char *api, char *dst, NvLength dst_size, NvBool seri_up);
NV_STATUS finnDeserializeInternal_FINN_RM_API(const char *src, NvLength src_size, char *api, NvLength api_size, NvBool deser_up);
/**@}*/


/*!
 * @brief Serializes an RM API control params struct and copies it into the
 *        serialization buffer as a FINN message.
 *
 * @note  FinnRmApiSerializeDown is for serializing down the call stack.
 *
 *        FinnRmApiSerializeUp is for serializing up the call stack.  It
 *        frees memory allocated by FinnRmApiDeserializeDown.  Use only
 *        when handling RM API control requests.
 *
 * @warning One of these may be unimplemented depending on platform. If both
 *          are implemented, misuse causes memory corruption and memory leaks.
 *
 * @param[in]      interface  FINN interface ID of the param struct.
 * @param[in]      message    FINN message ID of the param struct.
 * @param[in]      api        Source param struct from which to copy the data.
 * @param[in]      dst        Destination buffer into which to copy the data.
 * @param[in]      dst_size   Maximum size of the destination buffer measured in
 *                            `NvU8` units.
 *
 * @retval NV_OK                    Serialization successful.
 * @retval NV_ERR_INVALID_ARGUMENT  Bad function arguments, invalid union
 *                                  selector, or invalid enum value.
 * @retval NV_ERR_NOT_SUPPORTED     Unserializable or nonexistent ID.
 * @retval NV_ERR_NOT_COMPATIBLE     Container count too large.
 * @retval NV_ERR_OUT_OF_RANGE      Ranged field exceeded bounds.
 * @retval NV_ERR_BUFFER_TOO_SMALL  Destination buffer size too small.
 */
/**@{*/
static NV_INLINE NV_STATUS FinnRmApiSerializeUp(NvU64 interface, NvU64 message, const void *api, NvU8 *dst, NvLength dst_size)
{
    return finnSerializeInternal_FINN_RM_API(interface, message, (const char *) api, (char *) dst, dst_size, NV_TRUE);
}
static NV_INLINE NV_STATUS FinnRmApiSerializeDown(NvU64 interface, NvU64 message, const void *api, NvU8 *dst, NvLength dst_size)
{
    return finnSerializeInternal_FINN_RM_API(interface, message, (const char *) api, (char *) dst, dst_size, NV_FALSE);
}
/**@}*/


/*!
 * @brief The following APIs deserialize a FINN message from the serialization
 *        buffer and copy it into an RM API control params struct.
 *
 * @note  FinnRmApiDeserializeDown is for deserializing down the call stack. It
 *        allocates deep buffers for primitive pointers in the serialization
 *        buffer, assuming that it remains in memory. Use only when handling
 *        RM API control requests.
 *
 *        FinnRmApiDeserializeUp is for deserializing up the call stack. It
 *        copies deep buffers of primitive pointers into the params struct,
 *        assuming that memory is already allocated for them. Use only when
 *        receiving RM API control results.
 *
 * @warning One of these may be unimplemented depending on platform. If both
 *          are implemented, misuse causes memory corruption and memory leaks.
 *
 * @param[in]      src        Source buffer from which to copy the data.
 * @param[in]      src_size   Maximum size of the source buffer measured in
 *                            `NvU8` units.
 * @param[in, out] api        Destination param struct into which to copy the data.
 * @param[in]      api_size   Size of the destination param struct measured in
 *                            `char` units per `sizeof` operator.
 *
 * @retval NV_OK                          Deserialization successful.
 * @retval NV_ERR_INVALID_ARGUMENT        Bad function arguments, invalid union
 *                                        selector, invalid enum value, or
 *                                        mismatch between expected and actual
 *                                        serialized size.
 * @retval NV_ERR_NOT_SUPPORTED           Unserializable or nonexistent ID.
 * @retval NV_ERR_OUT_OF_RANGE            Ranged field exceeded bounds.
 * @retval NV_ERR_BUFFER_TOO_SMALL        Source/destination buffer too small.
 * @retval NV_ERR_LIB_RM_VERSION_MISMATCH Version mismatch.
 */
/**@{*/
static NV_INLINE NV_STATUS FinnRmApiDeserializeDown(NvU8 *src, NvLength src_size, void *api, NvLength api_size)
{
    return finnDeserializeInternal_FINN_RM_API((const char *) src, src_size / sizeof(NvU8), (char *) api, api_size, NV_FALSE);
}
static NV_INLINE NV_STATUS FinnRmApiDeserializeUp(NvU8 *src, NvLength src_size, void *api, NvLength api_size)
{
    return finnDeserializeInternal_FINN_RM_API((const char *) src, src_size / sizeof(NvU8), (char *) api, api_size, NV_TRUE);
}
/**@}*/


/*!
 * @brief Calculates the serialized size of an RM API param struct.
 *
 * @param[in]       interface   FINN interface ID of the param struct.
 * @param[in]       message     FINN message ID of the param struct.
 * @param[in]       src         Pointer to the param struct.
 *
 * @retval          Non-zero serialized size of param struct on success.
 * @retval          0 if the API is unsupported by serialization or src is NULL.
 */
NvU64 FinnRmApiGetSerializedSize(NvU64 interface, NvU64 message, const NvP64 src);


/*!
 * @brief Fetches the unserialized size of an API param struct.
 *
 * @note The size is measured in `char` units like the `sizeof` operator.
 *
 * @param[in]       interface   FINN interface ID of the param struct.
 * @param[in]       message     FINN message ID of the param struct.
 *
 * @retval          Non-zero sizeof param struct on success.
 * @retval          0 if the API is unsupported by serialization.
 */
NvU64 FinnRmApiGetUnserializedSize(NvU64 interface, NvU64 message);


#define NV_RM_ALLOC_INTERFACE_INTERFACE_ID (0xA000U)
typedef FINN_RM_API NV_RM_ALLOC_INTERFACE;
#define FINN_NV01_ROOT_RESERVED_INTERFACE_ID (0x0U)
typedef FINN_RM_API FINN_NV01_ROOT_RESERVED;
#define FINN_NV01_ROOT_CLIENT_INTERFACE_ID (0xdU)
typedef FINN_RM_API FINN_NV01_ROOT_CLIENT;
#define FINN_NV01_ROOT_DIAG_INTERFACE_ID (0x4U)
typedef FINN_RM_API FINN_NV01_ROOT_DIAG;
#define FINN_NV01_ROOT_EVENT_INTERFACE_ID (0x5U)
typedef FINN_RM_API FINN_NV01_ROOT_EVENT;
#define FINN_NV01_ROOT_GPU_INTERFACE_ID (0x2U)
typedef FINN_RM_API FINN_NV01_ROOT_GPU;
#define FINN_NV01_ROOT_GPUACCT_INTERFACE_ID (0xbU)
typedef FINN_RM_API FINN_NV01_ROOT_GPUACCT;
#define FINN_NV01_ROOT_GSYNC_INTERFACE_ID (0x3U)
typedef FINN_RM_API FINN_NV01_ROOT_GSYNC;
#define FINN_NV01_ROOT_NVD_INTERFACE_ID (0x6U)
typedef FINN_RM_API FINN_NV01_ROOT_NVD;
#define FINN_NV01_ROOT_PROC_INTERFACE_ID (0x9U)
typedef FINN_RM_API FINN_NV01_ROOT_PROC;

#define FINN_NV01_ROOT_SYNC_GPU_BOOST_INTERFACE_ID (0xaU)
typedef FINN_RM_API FINN_NV01_ROOT_SYNC_GPU_BOOST;
#define FINN_NV01_ROOT_SYSTEM_INTERFACE_ID (0x1U)
typedef FINN_RM_API FINN_NV01_ROOT_SYSTEM;
#define FINN_NV01_ROOT_OS_UNIX_INTERFACE_ID (0x3dU)
typedef FINN_RM_API FINN_NV01_ROOT_OS_UNIX;
#define FINN_NV01_ROOT_VGPU_INTERFACE_ID (0xcU)
typedef FINN_RM_API FINN_NV01_ROOT_VGPU;
#define FINN_NV01_ROOT_OS_WINDOWS_INTERFACE_ID (0x3fU)
typedef FINN_RM_API FINN_NV01_ROOT_OS_WINDOWS;
#define FINN_NV01_CONTEXT_DMA_RESERVED_INTERFACE_ID (0x200U)
typedef FINN_RM_API FINN_NV01_CONTEXT_DMA_RESERVED;
#define FINN_NV01_CONTEXT_DMA_DMA_INTERFACE_ID (0x201U)
typedef FINN_RM_API FINN_NV01_CONTEXT_DMA_DMA;
#define FINN_NV01_TIMER_RESERVED_INTERFACE_ID (0x400U)
typedef FINN_RM_API FINN_NV01_TIMER_RESERVED;
#define FINN_NV01_TIMER_TMR_INTERFACE_ID (0x401U)
typedef FINN_RM_API FINN_NV01_TIMER_TMR;
#define FINN_FABRIC_MANAGER_SESSION_RESERVED_INTERFACE_ID (0xf00U)
typedef FINN_RM_API FINN_FABRIC_MANAGER_SESSION_RESERVED;
#define FINN_FABRIC_MANAGER_SESSION_FM_INTERFACE_ID (0xf01U)
typedef FINN_RM_API FINN_FABRIC_MANAGER_SESSION_FM;
#define FINN_NV0020_GPU_MANAGEMENT_RESERVED_INTERFACE_ID (0x2000U)
typedef FINN_RM_API FINN_NV0020_GPU_MANAGEMENT_RESERVED;
#define FINN_NV0020_GPU_MANAGEMENT_GPU_MGMT_INTERFACE_ID (0x2001U)
typedef FINN_RM_API FINN_NV0020_GPU_MANAGEMENT_GPU_MGMT;
#define FINN_NV01_MEMORY_SYSTEM_RESERVED_INTERFACE_ID (0x3e00U)
typedef FINN_RM_API FINN_NV01_MEMORY_SYSTEM_RESERVED;
#define FINN_NV01_MEMORY_SYSTEM_MEMORY_INTERFACE_ID (0x3e01U)
typedef FINN_RM_API FINN_NV01_MEMORY_SYSTEM_MEMORY;
#define FINN_NV01_ROOT_USER_RESERVED_INTERFACE_ID (0x4100U)
typedef FINN_RM_API FINN_NV01_ROOT_USER_RESERVED;
#define FINN_NV01_ROOT_USER_MEMORY_INTERFACE_ID (0x4101U)
typedef FINN_RM_API FINN_NV01_ROOT_USER_MEMORY;
#define FINN_NV_CE_UTILS_RESERVED_INTERFACE_ID (0x0050U)
typedef FINN_RM_API FINN_NV_CE_UTILS_RESERVED;
#define FINN_NV_CE_UTILS_UTILS_INTERFACE_ID (0x5001U)
typedef FINN_RM_API FINN_NV_CE_UTILS_UTILS;
#define FINN_NV04_DISPLAY_COMMON_RESERVED_INTERFACE_ID (0x7300U)
typedef FINN_RM_API FINN_NV04_DISPLAY_COMMON_RESERVED;
#define FINN_NV04_DISPLAY_COMMON_COMMON_INTERFACE_ID (0x7305U)
typedef FINN_RM_API FINN_NV04_DISPLAY_COMMON_COMMON;
#define FINN_NV04_DISPLAY_COMMON_DFP_INTERFACE_ID (0x7311U)
typedef FINN_RM_API FINN_NV04_DISPLAY_COMMON_DFP;
#define FINN_NV04_DISPLAY_COMMON_DP_INTERFACE_ID (0x7313U)
typedef FINN_RM_API FINN_NV04_DISPLAY_COMMON_DP;

#define FINN_NV04_DISPLAY_COMMON_EVENT_INTERFACE_ID (0x7303U)
typedef FINN_RM_API FINN_NV04_DISPLAY_COMMON_EVENT;
#define FINN_NV04_DISPLAY_COMMON_INTERNAL_INTERFACE_ID (0x7304U)
typedef FINN_RM_API FINN_NV04_DISPLAY_COMMON_INTERNAL;
#define FINN_NV04_DISPLAY_COMMON_PSR_INTERFACE_ID (0x7316U)
typedef FINN_RM_API FINN_NV04_DISPLAY_COMMON_PSR;
#define FINN_NV04_DISPLAY_COMMON_SPECIFIC_INTERFACE_ID (0x7302U)
typedef FINN_RM_API FINN_NV04_DISPLAY_COMMON_SPECIFIC;
#define FINN_NV04_DISPLAY_COMMON_STEREO_INTERFACE_ID (0x7317U)
typedef FINN_RM_API FINN_NV04_DISPLAY_COMMON_STEREO;

#define FINN_NV04_DISPLAY_COMMON_SYSTEM_INTERFACE_ID (0x7301U)
typedef FINN_RM_API FINN_NV04_DISPLAY_COMMON_SYSTEM;
#define FINN_NV01_FRAMEBUFFER_CONSOLE_INTERFACE_ID (0x007601U)
typedef FINN_RM_API FINN_NV01_FRAMEBUFFER_CONSOLE;
#define FINN_NV01_DEVICE_0_RESERVED_INTERFACE_ID (0x8000U)
typedef FINN_RM_API FINN_NV01_DEVICE_0_RESERVED;
#define FINN_NV01_DEVICE_0_BIF_INTERFACE_ID (0x8001U)
typedef FINN_RM_API FINN_NV01_DEVICE_0_BIF;
#define FINN_NV01_DEVICE_0_BSP_INTERFACE_ID (0x801cU)
typedef FINN_RM_API FINN_NV01_DEVICE_0_BSP;

#define FINN_NV01_DEVICE_0_DMA_INTERFACE_ID (0x8018U)
typedef FINN_RM_API FINN_NV01_DEVICE_0_DMA;
#define FINN_NV01_DEVICE_0_FB_INTERFACE_ID (0x8013U)
typedef FINN_RM_API FINN_NV01_DEVICE_0_FB;
#define FINN_NV01_DEVICE_0_FIFO_INTERFACE_ID (0x8017U)
typedef FINN_RM_API FINN_NV01_DEVICE_0_FIFO;
#define FINN_NV01_DEVICE_0_GPU_INTERFACE_ID (0x8002U)
typedef FINN_RM_API FINN_NV01_DEVICE_0_GPU;
#define FINN_NV01_DEVICE_0_GR_INTERFACE_ID (0x8011U)
typedef FINN_RM_API FINN_NV01_DEVICE_0_GR;
#define FINN_NV01_DEVICE_0_HOST_INTERFACE_ID (0x8014U)
typedef FINN_RM_API FINN_NV01_DEVICE_0_HOST;
#define FINN_NV01_DEVICE_0_INTERNAL_INTERFACE_ID (0x8020U)
typedef FINN_RM_API FINN_NV01_DEVICE_0_INTERNAL;
#define FINN_NV01_DEVICE_0_MSENC_INTERFACE_ID (0x801bU)
typedef FINN_RM_API FINN_NV01_DEVICE_0_MSENC;
#define FINN_NV01_DEVICE_0_NVJPG_INTERFACE_ID (0x801fU)
typedef FINN_RM_API FINN_NV01_DEVICE_0_NVJPG;
#define FINN_NV01_DEVICE_0_PERF_INTERFACE_ID (0x8019U)
typedef FINN_RM_API FINN_NV01_DEVICE_0_PERF;

#define FINN_NV01_DEVICE_0_OS_UNIX_INTERFACE_ID (0x801eU)
typedef FINN_RM_API FINN_NV01_DEVICE_0_OS_UNIX;

#define FINN_NV0090_KERNEL_GRAPHICS_CONTEXT_INTERFACE_ID (0x9001U)
typedef FINN_RM_API FINN_NV0090_KERNEL_GRAPHICS_CONTEXT;
#define FINN_NV_SEMAPHORE_SURFACE_INTERFACE_ID (0x00da00U)
typedef FINN_RM_API FINN_NV_SEMAPHORE_SURFACE;
#define FINN_RM_USER_SHARED_DATA_INTERFACE_ID (0xde00U)
typedef FINN_RM_API FINN_RM_USER_SHARED_DATA;
#define FINN_NV_MEMORY_EXPORT_RESERVED_INTERFACE_ID (0xE000U)
typedef FINN_RM_API FINN_NV_MEMORY_EXPORT_RESERVED;
#define FINN_NV_MEMORY_EXPORT_INTERFACE_ID (0xE001U)
typedef FINN_RM_API FINN_NV_MEMORY_EXPORT;
#define FINN_IMEX_SESSION_INTERFACE_ID (0xf100U)
typedef FINN_RM_API FINN_IMEX_SESSION;
#define FINN_NV_MEMORY_FABRIC_RESERVED_INTERFACE_ID (0xf800U)
typedef FINN_RM_API FINN_NV_MEMORY_FABRIC_RESERVED;
#define FINN_NV_MEMORY_FABRIC_FABRIC_INTERFACE_ID (0xf801U)
typedef FINN_RM_API FINN_NV_MEMORY_FABRIC_FABRIC;
#define FINN_NV_MEMORY_FABRIC_IMPORT_V2_RESERVED_INTERFACE_ID (0xf900U)
typedef FINN_RM_API FINN_NV_MEMORY_FABRIC_IMPORT_V2_RESERVED;
#define FINN_NV_MEMORY_FABRIC_IMPORT_V2_IMPORT_INTERFACE_ID (0xf901U)
typedef FINN_RM_API FINN_NV_MEMORY_FABRIC_IMPORT_V2_IMPORT;
#define FINN_NV_MEMORY_FABRIC_IMPORTED_REF_RESERVED_INTERFACE_ID (0xfb00U)
typedef FINN_RM_API FINN_NV_MEMORY_FABRIC_IMPORTED_REF_RESERVED;
#define FINN_NV_MEMORY_FABRIC_IMPORTED_REF_IMPORT_REF_INTERFACE_ID (0xfb01U)
typedef FINN_RM_API FINN_NV_MEMORY_FABRIC_IMPORTED_REF_IMPORT_REF;
#define FINN_NV_MEMORY_MULTICAST_FABRIC_RESERVED_INTERFACE_ID (0xfd00U)
typedef FINN_RM_API FINN_NV_MEMORY_MULTICAST_FABRIC_RESERVED;
#define FINN_NV_MEMORY_MULTICAST_FABRIC_FABRIC_INTERFACE_ID (0xfd01U)
typedef FINN_RM_API FINN_NV_MEMORY_MULTICAST_FABRIC_FABRIC;
#define FINN_NV_MEMORY_MAPPER_INTERFACE_ID (0xfe01U)
typedef FINN_RM_API FINN_NV_MEMORY_MAPPER;
#define FINN_LOCK_STRESS_OBJECT_RESERVED_INTERFACE_ID (0x10000U)
typedef FINN_RM_API FINN_LOCK_STRESS_OBJECT_RESERVED;
#define FINN_LOCK_STRESS_OBJECT_LOCK_STRESS_INTERFACE_ID (0x10001U)
typedef FINN_RM_API FINN_LOCK_STRESS_OBJECT_LOCK_STRESS;

#define FINN_NV20_SUBDEVICE_0_RESERVED_INTERFACE_ID (0x208000U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_RESERVED;

#define FINN_NV20_SUBDEVICE_0_BIOS_INTERFACE_ID (0x208008U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_BIOS;
#define FINN_NV20_SUBDEVICE_0_BUS_INTERFACE_ID (0x208018U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_BUS;
#define FINN_NV20_SUBDEVICE_0_CE_INTERFACE_ID (0x20802aU)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_CE;

#define FINN_NV20_SUBDEVICE_0_CLK_INTERFACE_ID (0x208010U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_CLK;

#define FINN_NV20_SUBDEVICE_0_DMA_INTERFACE_ID (0x208025U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_DMA;
#define FINN_NV20_SUBDEVICE_0_DMABUF_INTERFACE_ID (0x20803AU)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_DMABUF;
#define FINN_NV20_SUBDEVICE_0_ECC_INTERFACE_ID (0x208034U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_ECC;

#define FINN_NV20_SUBDEVICE_0_EVENT_INTERFACE_ID (0x208003U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_EVENT;
#define FINN_NV20_SUBDEVICE_0_THERMAL_INTERFACE_ID (0x208005U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_THERMAL;

#define FINN_NV20_SUBDEVICE_0_FB_INTERFACE_ID (0x208013U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_FB;
#define FINN_NV20_SUBDEVICE_0_FIFO_INTERFACE_ID (0x208011U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_FIFO;
#define FINN_NV20_SUBDEVICE_0_FLA_INTERFACE_ID (0x208035U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_FLA;
#define FINN_NV20_SUBDEVICE_0_FLCN_INTERFACE_ID (0x208031U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_FLCN;
#define FINN_NV20_SUBDEVICE_0_FUSE_INTERFACE_ID (0x208002U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_FUSE;

#define FINN_NV20_SUBDEVICE_0_GPIO_INTERFACE_ID (0x208023U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_GPIO;

#define FINN_NV20_SUBDEVICE_0_GPU_INTERFACE_ID (0x208001U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_GPU;

#define FINN_NV20_SUBDEVICE_0_GR_INTERFACE_ID (0x208012U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_GR;
#define FINN_NV20_SUBDEVICE_0_GRMGR_INTERFACE_ID (0x208038U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_GRMGR;
#define FINN_NV20_SUBDEVICE_0_GSP_INTERFACE_ID (0x208036U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_GSP;
#define FINN_NV20_SUBDEVICE_0_HSHUB_INTERFACE_ID (0x208041U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_HSHUB;
#define FINN_NV20_SUBDEVICE_0_I2C_INTERFACE_ID (0x208006U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_I2C;
#define FINN_NV20_SUBDEVICE_0_PMGR_INTERFACE_ID (0x208026U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_PMGR;

#define FINN_NV20_SUBDEVICE_0_INTERNAL_INTERFACE_ID (0x20800aU)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_INTERNAL;
#define FINN_NV20_SUBDEVICE_0_INTERNAL_2_INTERFACE_ID (0x20800bU)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_INTERNAL_2;
#define FINN_NV20_SUBDEVICE_0_LPWR_INTERFACE_ID (0x208028U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_LPWR;

#define FINN_NV20_SUBDEVICE_0_MC_INTERFACE_ID (0x208017U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_MC;
#define FINN_NV20_SUBDEVICE_0_NNE_INTERFACE_ID (0x208037U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_NNE;

#define FINN_NV20_SUBDEVICE_0_NVD_INTERFACE_ID (0x208024U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_NVD;

#define FINN_NV20_SUBDEVICE_0_NVLINK_INTERFACE_ID (0x208030U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_NVLINK;

#define FINN_NV20_SUBDEVICE_0_PERF_INTERFACE_ID (0x208020U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_PERF;

#define FINN_NV20_SUBDEVICE_0_POWER_INTERFACE_ID (0x208027U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_POWER;

#define FINN_NV20_SUBDEVICE_0_RC_INTERFACE_ID (0x208022U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_RC;

#define FINN_NV20_SUBDEVICE_0_SEC2_INTERFACE_ID (0x208042U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_SEC2;

#define FINN_NV20_SUBDEVICE_0_TIMER_INTERFACE_ID (0x208004U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_TIMER;

#define FINN_NV20_SUBDEVICE_0_OS_UNIX_INTERFACE_ID (0x20803dU)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_OS_UNIX;
#define FINN_NV20_SUBDEVICE_0_VGPU_MGR_INTERNAL_INTERFACE_ID (0x208040U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_VGPU_MGR_INTERNAL;
#define FINN_NV20_SUBDEVICE_0_VOLT_INTERFACE_ID (0x208032U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_0_VOLT;

#define FINN_NV2081_BINAPI_RESERVED_INTERFACE_ID (0x208100U)
typedef FINN_RM_API FINN_NV2081_BINAPI_RESERVED;
#define FINN_NV2081_BINAPI_INTERFACE_ID (0x208101U)
typedef FINN_RM_API FINN_NV2081_BINAPI;
#define FINN_NV2082_BINAPI_RESERVED_INTERFACE_ID (0x208200U)
typedef FINN_RM_API FINN_NV2082_BINAPI_RESERVED;
#define FINN_NV2082_BINAPI_INTERFACE_ID (0x208201U)
typedef FINN_RM_API FINN_NV2082_BINAPI;
#define FINN_NV20_SUBDEVICE_DIAG_RESERVED_INTERFACE_ID (0x208f00U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_RESERVED;
#define FINN_NV20_SUBDEVICE_DIAG_BIF_INTERFACE_ID (0x208f07U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_BIF;
#define FINN_NV20_SUBDEVICE_DIAG_BUS_INTERFACE_ID (0x208f18U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_BUS;

#define FINN_NV20_SUBDEVICE_DIAG_DMA_INTERFACE_ID (0x208f14U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_DMA;
#define FINN_NV20_SUBDEVICE_DIAG_EVENT_INTERFACE_ID (0x208f10U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_EVENT;
#define FINN_NV20_SUBDEVICE_DIAG_FB_INTERFACE_ID (0x208f05U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_FB;
#define FINN_NV20_SUBDEVICE_DIAG_FBIO_INTERFACE_ID (0x208f0aU)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_FBIO;
#define FINN_NV20_SUBDEVICE_DIAG_FIFO_INTERFACE_ID (0x208f04U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_FIFO;
#define FINN_NV20_SUBDEVICE_DIAG_GPU_INTERFACE_ID (0x208f11U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_GPU;
#define FINN_NV20_SUBDEVICE_DIAG_GR_INTERFACE_ID (0x208f12U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_GR;

#define FINN_NV20_SUBDEVICE_DIAG_MMU_INTERFACE_ID (0x208f0bU)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_MMU;
#define FINN_NV20_SUBDEVICE_DIAG_NVLINK_INTERFACE_ID (0x208f1AU)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_NVLINK;

#define FINN_NV20_SUBDEVICE_DIAG_PMU_INTERFACE_ID (0x208f0cU)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_PMU;

#define FINN_NV20_SUBDEVICE_DIAG_UCODE_COVERAGE_INTERFACE_ID (0x208f19U)
typedef FINN_RM_API FINN_NV20_SUBDEVICE_DIAG_UCODE_COVERAGE;
#define FINN_NV30_GSYNC_RESERVED_INTERFACE_ID (0x30f100U)
typedef FINN_RM_API FINN_NV30_GSYNC_RESERVED;
#define FINN_NV30_GSYNC_GSYNC_INTERFACE_ID (0x30f101U)
typedef FINN_RM_API FINN_NV30_GSYNC_GSYNC;
#define FINN_NV40_I2C_RESERVED_INTERFACE_ID (0x402c00U)
typedef FINN_RM_API FINN_NV40_I2C_RESERVED;
#define FINN_NV40_I2C_I2C_INTERFACE_ID (0x402c01U)
typedef FINN_RM_API FINN_NV40_I2C_I2C;
#define FINN_NV50_THIRD_PARTY_P2P_P2P_INTERFACE_ID (0x503c01U)
typedef FINN_RM_API FINN_NV50_THIRD_PARTY_P2P_P2P;
#define FINN_NV50_THIRD_PARTY_P2P_RESERVED_INTERFACE_ID (0x503c00U)
typedef FINN_RM_API FINN_NV50_THIRD_PARTY_P2P_RESERVED;
#define FINN_NV50_CHANNEL_GPFIFO_RESERVED_INTERFACE_ID (0x506f00U)
typedef FINN_RM_API FINN_NV50_CHANNEL_GPFIFO_RESERVED;
#define FINN_NV50_CHANNEL_GPFIFO_GPFIFO_INTERFACE_ID (0x506f01U)
typedef FINN_RM_API FINN_NV50_CHANNEL_GPFIFO_GPFIFO;
#define FINN_NV50_DISPLAY_RESERVED_INTERFACE_ID (0x507000U)
typedef FINN_RM_API FINN_NV50_DISPLAY_RESERVED;
#define FINN_NV50_DISPLAY_CHNCTL_INTERFACE_ID (0x507001U)
typedef FINN_RM_API FINN_NV50_DISPLAY_CHNCTL;
#define FINN_NV50_DISPLAY_OR_INTERFACE_ID (0x507004U)
typedef FINN_RM_API FINN_NV50_DISPLAY_OR;
#define FINN_NV50_DISPLAY_RG_INTERFACE_ID (0x507002U)
typedef FINN_RM_API FINN_NV50_DISPLAY_RG;
#define FINN_NV50_DISPLAY_SYSTEM_INTERFACE_ID (0x507007U)
typedef FINN_RM_API FINN_NV50_DISPLAY_SYSTEM;

#define FINN_NV50_DEFERRED_API_CLASS_RESERVED_INTERFACE_ID (0x508000U)
typedef FINN_RM_API FINN_NV50_DEFERRED_API_CLASS_RESERVED;
#define FINN_NV50_DEFERRED_API_CLASS_DEFERRED_INTERFACE_ID (0x508001U)
typedef FINN_RM_API FINN_NV50_DEFERRED_API_CLASS_DEFERRED;
#define FINN_GT200_DEBUGGER_RESERVED_INTERFACE_ID (0x83de00U)
typedef FINN_RM_API FINN_GT200_DEBUGGER_RESERVED;
#define FINN_GT200_DEBUGGER_DEBUG_INTERFACE_ID (0x83de03U)
typedef FINN_RM_API FINN_GT200_DEBUGGER_DEBUG;
#define FINN_GT200_DEBUGGER_FIFO_INTERFACE_ID (0x83de02U)
typedef FINN_RM_API FINN_GT200_DEBUGGER_FIFO;
#define FINN_GT200_DEBUGGER_INTERNAL_INTERFACE_ID (0x83de04U)
typedef FINN_RM_API FINN_GT200_DEBUGGER_INTERNAL;

#define FINN_NV9010_VBLANK_CALLBACK_RESERVED_INTERFACE_ID (0x901000U)
typedef FINN_RM_API FINN_NV9010_VBLANK_CALLBACK_RESERVED;
#define FINN_NV9010_VBLANK_CALLBACK_INTERFACE_ID (0x901001U)
typedef FINN_RM_API FINN_NV9010_VBLANK_CALLBACK;
#define FINN_FERMI_CONTEXT_SHARE_A_RESERVED_INTERFACE_ID (0x906700U)
typedef FINN_RM_API FINN_FERMI_CONTEXT_SHARE_A_RESERVED;
#define FINN_FERMI_CONTEXT_SHARE_A_TPC_PARTITION_INTERFACE_ID (0x906701U)
typedef FINN_RM_API FINN_FERMI_CONTEXT_SHARE_A_TPC_PARTITION;
#define FINN_FERMI_CONTEXT_SHARE_A_CWD_WATERMARK_INTERFACE_ID (0x906702U)
typedef FINN_RM_API FINN_FERMI_CONTEXT_SHARE_A_CWD_WATERMARK;
#define FINN_GF100_CHANNEL_GPFIFO_RESERVED_INTERFACE_ID (0x906f00U)
typedef FINN_RM_API FINN_GF100_CHANNEL_GPFIFO_RESERVED;
#define FINN_GF100_CHANNEL_GPFIFO_GPFIFO_INTERFACE_ID (0x906f01U)
typedef FINN_RM_API FINN_GF100_CHANNEL_GPFIFO_GPFIFO;
#define FINN_GF100_DISP_SW_RESERVED_INTERFACE_ID (0x907200U)
typedef FINN_RM_API FINN_GF100_DISP_SW_RESERVED;
#define FINN_GF100_DISP_SW_DISP_SW_INTERFACE_ID (0x907201U)
typedef FINN_RM_API FINN_GF100_DISP_SW_DISP_SW;
#define FINN_GF100_TIMED_SEMAPHORE_SW_RESERVED_INTERFACE_ID (0x907400U)
typedef FINN_RM_API FINN_GF100_TIMED_SEMAPHORE_SW_RESERVED;
#define FINN_GF100_TIMED_SEMAPHORE_SW_SEM_INTERFACE_ID (0x907401U)
typedef FINN_RM_API FINN_GF100_TIMED_SEMAPHORE_SW_SEM;
#define FINN_GF100_REMAPPER_RESERVED_INTERFACE_ID (0x907f00U)
typedef FINN_RM_API FINN_GF100_REMAPPER_RESERVED;
#define FINN_GF100_REMAPPER_REMAPPER_INTERFACE_ID (0x907f01U)
typedef FINN_RM_API FINN_GF100_REMAPPER_REMAPPER;
#define FINN_GF100_ZBC_CLEAR_RESERVED_INTERFACE_ID (0x909600U)
typedef FINN_RM_API FINN_GF100_ZBC_CLEAR_RESERVED;
#define FINN_GF100_ZBC_CLEAR_ZBC_INTERFACE_ID (0x909601U)
typedef FINN_RM_API FINN_GF100_ZBC_CLEAR_ZBC;
#define FINN_GF100_PROFILER_RESERVED_INTERFACE_ID (0x90cc00U)
typedef FINN_RM_API FINN_GF100_PROFILER_RESERVED;
#define FINN_GF100_PROFILER_HWPM_INTERFACE_ID (0x90cc01U)
typedef FINN_RM_API FINN_GF100_PROFILER_HWPM;
#define FINN_GF100_PROFILER_NVLINK_INTERFACE_ID (0x90cc02U)
typedef FINN_RM_API FINN_GF100_PROFILER_NVLINK;
#define FINN_GF100_PROFILER_POWER_INTERFACE_ID (0x90cc03U)
typedef FINN_RM_API FINN_GF100_PROFILER_POWER;
#define FINN_NV_EVENT_BUFFER_RESERVED_INTERFACE_ID (0x90cd00U)
typedef FINN_RM_API FINN_NV_EVENT_BUFFER_RESERVED;
#define FINN_NV_EVENT_BUFFER_EVENT_INTERFACE_ID (0x90cd01U)
typedef FINN_RM_API FINN_NV_EVENT_BUFFER_EVENT;
#define FINN_GF100_SUBDEVICE_GRAPHICS_RESERVED_INTERFACE_ID (0x90e000U)
typedef FINN_RM_API FINN_GF100_SUBDEVICE_GRAPHICS_RESERVED;
#define FINN_GF100_SUBDEVICE_GRAPHICS_GRAPHICS_INTERFACE_ID (0x90e001U)
typedef FINN_RM_API FINN_GF100_SUBDEVICE_GRAPHICS_GRAPHICS;
#define FINN_GF100_SUBDEVICE_FB_RESERVED_INTERFACE_ID (0x90e100U)
typedef FINN_RM_API FINN_GF100_SUBDEVICE_FB_RESERVED;
#define FINN_GF100_SUBDEVICE_FB_FB_INTERFACE_ID (0x90e101U)
typedef FINN_RM_API FINN_GF100_SUBDEVICE_FB_FB;
#define FINN_GF100_SUBDEVICE_MASTER_RESERVED_INTERFACE_ID (0x90e600U)
typedef FINN_RM_API FINN_GF100_SUBDEVICE_MASTER_RESERVED;
#define FINN_GF100_SUBDEVICE_MASTER_MASTER_INTERFACE_ID (0x90e601U)
typedef FINN_RM_API FINN_GF100_SUBDEVICE_MASTER_MASTER;
#define FINN_GF100_SUBDEVICE_INFOROM_RESERVED_INTERFACE_ID (0x90e700U)
typedef FINN_RM_API FINN_GF100_SUBDEVICE_INFOROM_RESERVED;
#define FINN_GF100_SUBDEVICE_INFOROM_BBX_INTERFACE_ID (0x90e701U)
typedef FINN_RM_API FINN_GF100_SUBDEVICE_INFOROM_BBX;

#define FINN_GF100_HDACODEC_RESERVED_INTERFACE_ID (0x90ec00U)
typedef FINN_RM_API FINN_GF100_HDACODEC_RESERVED;
#define FINN_GF100_HDACODEC_HDACODEC_INTERFACE_ID (0x90ec01U)
typedef FINN_RM_API FINN_GF100_HDACODEC_HDACODEC;
#define FINN_FERMI_VASPACE_A_RESERVED_INTERFACE_ID (0x90f100U)
typedef FINN_RM_API FINN_FERMI_VASPACE_A_RESERVED;
#define FINN_FERMI_VASPACE_A_VASPACE_INTERFACE_ID (0x90f101U)
typedef FINN_RM_API FINN_FERMI_VASPACE_A_VASPACE;
#define FINN_KEPLER_CHANNEL_GROUP_A_RESERVED_INTERFACE_ID (0xa06c00U)
typedef FINN_RM_API FINN_KEPLER_CHANNEL_GROUP_A_RESERVED;
#define FINN_KEPLER_CHANNEL_GROUP_A_GPFIFO_INTERFACE_ID (0xa06c01U)
typedef FINN_RM_API FINN_KEPLER_CHANNEL_GROUP_A_GPFIFO;
#define FINN_KEPLER_CHANNEL_GROUP_A_INTERNAL_INTERFACE_ID (0xa06c02U)
typedef FINN_RM_API FINN_KEPLER_CHANNEL_GROUP_A_INTERNAL;
#define FINN_KEPLER_CHANNEL_GPFIFO_A_RESERVED_INTERFACE_ID (0xa06f00U)
typedef FINN_RM_API FINN_KEPLER_CHANNEL_GPFIFO_A_RESERVED;
#define FINN_KEPLER_CHANNEL_GPFIFO_A_GPFIFO_INTERFACE_ID (0xa06f01U)
typedef FINN_RM_API FINN_KEPLER_CHANNEL_GPFIFO_A_GPFIFO;
#define FINN_KEPLER_CHANNEL_GPFIFO_A_INTERNAL_INTERFACE_ID (0xa06f03U)
typedef FINN_RM_API FINN_KEPLER_CHANNEL_GPFIFO_A_INTERNAL;
#define FINN_KEPLER_DEVICE_VGPU_RESERVED_INTERFACE_ID (0xa08000U)
typedef FINN_RM_API FINN_KEPLER_DEVICE_VGPU_RESERVED;
#define FINN_KEPLER_DEVICE_VGPU_VGPU_DISPLAY_INTERFACE_ID (0xa08001U)
typedef FINN_RM_API FINN_KEPLER_DEVICE_VGPU_VGPU_DISPLAY;
#define FINN_KEPLER_DEVICE_VGPU_VGPU_MEMORY_INTERFACE_ID (0xa08002U)
typedef FINN_RM_API FINN_KEPLER_DEVICE_VGPU_VGPU_MEMORY;
#define FINN_KEPLER_DEVICE_VGPU_VGPU_OTHERS_INTERFACE_ID (0xa08003U)
typedef FINN_RM_API FINN_KEPLER_DEVICE_VGPU_VGPU_OTHERS;
#define FINN_NVA081_VGPU_CONFIG_VGPU_CONFIG_INTERFACE_ID (0xa08101U)
typedef FINN_RM_API FINN_NVA081_VGPU_CONFIG_VGPU_CONFIG;

#define FINN_NVA083_GRID_DISPLAYLESS_RESERVED_INTERFACE_ID (0xa08300U)
typedef FINN_RM_API FINN_NVA083_GRID_DISPLAYLESS_RESERVED;
#define FINN_NVA083_GRID_DISPLAYLESS_VIRTUAL_DISPLAY_INTERFACE_ID (0xa08301U)
typedef FINN_RM_API FINN_NVA083_GRID_DISPLAYLESS_VIRTUAL_DISPLAY;
#define FINN_NVA084_KERNEL_HOST_VGPU_DEVICE_KERNEL_HOST_VGPU_DEVICE_INTERFACE_ID (0xa08401U)
typedef FINN_RM_API FINN_NVA084_KERNEL_HOST_VGPU_DEVICE_KERNEL_HOST_VGPU_DEVICE;
#define FINN_NVENC_SW_SESSION_NVENC_SW_SESSION_INTERFACE_ID (0xa0bc01U)
typedef FINN_RM_API FINN_NVENC_SW_SESSION_NVENC_SW_SESSION;
#define FINN_NVFBC_SW_SESSION_NVFBC_SW_SESSION_INTERFACE_ID (0xa0bd01U)
typedef FINN_RM_API FINN_NVFBC_SW_SESSION_NVFBC_SW_SESSION;
#define FINN_GK110_SUBDEVICE_GRAPHICS_RESERVED_INTERFACE_ID (0xa0e000U)
typedef FINN_RM_API FINN_GK110_SUBDEVICE_GRAPHICS_RESERVED;
#define FINN_GK110_SUBDEVICE_GRAPHICS_GRAPHICS_INTERFACE_ID (0xa0e001U)
typedef FINN_RM_API FINN_GK110_SUBDEVICE_GRAPHICS_GRAPHICS;
#define FINN_GK110_SUBDEVICE_FB_RESERVED_INTERFACE_ID (0xa0e100U)
typedef FINN_RM_API FINN_GK110_SUBDEVICE_FB_RESERVED;
#define FINN_GK110_SUBDEVICE_FB_FB_INTERFACE_ID (0xa0e101U)
typedef FINN_RM_API FINN_GK110_SUBDEVICE_FB_FB;
#define FINN_KEPLER_CHANNEL_GPFIFO_B_RESERVED_INTERFACE_ID (0xa16f00U)
typedef FINN_RM_API FINN_KEPLER_CHANNEL_GPFIFO_B_RESERVED;
#define FINN_KEPLER_CHANNEL_GPFIFO_C_RESERVED_INTERFACE_ID (0xa26f00U)
typedef FINN_RM_API FINN_KEPLER_CHANNEL_GPFIFO_C_RESERVED;
#define FINN_MAXWELL_FAULT_BUFFER_A_RESERVED_INTERFACE_ID (0xb06900U)
typedef FINN_RM_API FINN_MAXWELL_FAULT_BUFFER_A_RESERVED;
#define FINN_MAXWELL_FAULT_BUFFER_A_FAULTBUFFER_INTERFACE_ID (0xb06901U)
typedef FINN_RM_API FINN_MAXWELL_FAULT_BUFFER_A_FAULTBUFFER;
#define FINN_MAXWELL_CHANNEL_GPFIFO_A_RESERVED_INTERFACE_ID (0xb06f00U)
typedef FINN_RM_API FINN_MAXWELL_CHANNEL_GPFIFO_A_RESERVED;
#define FINN_MAXWELL_CHANNEL_GPFIFO_A_GPFIFO_INTERFACE_ID (0xb06f01U)
typedef FINN_RM_API FINN_MAXWELL_CHANNEL_GPFIFO_A_GPFIFO;
#define FINN_MAXWELL_PROFILER_RESERVED_INTERFACE_ID (0xb0cc00U)
typedef FINN_RM_API FINN_MAXWELL_PROFILER_RESERVED;
#define FINN_MAXWELL_PROFILER_INTERNAL_INTERFACE_ID (0xb0cc02U)
typedef FINN_RM_API FINN_MAXWELL_PROFILER_INTERNAL;
#define FINN_MAXWELL_PROFILER_POWER_INTERFACE_ID (0xb0cc03U)
typedef FINN_RM_API FINN_MAXWELL_PROFILER_POWER;
#define FINN_MAXWELL_PROFILER_PROFILER_INTERFACE_ID (0xb0cc01U)
typedef FINN_RM_API FINN_MAXWELL_PROFILER_PROFILER;
#define FINN_MAXWELL_PROFILER_CONTEXT_RESERVED_INTERFACE_ID (0xb1cc00U)
typedef FINN_RM_API FINN_MAXWELL_PROFILER_CONTEXT_RESERVED;
#define FINN_MAXWELL_PROFILER_CONTEXT_PROFILER_INTERFACE_ID (0xb1cc01U)
typedef FINN_RM_API FINN_MAXWELL_PROFILER_CONTEXT_PROFILER;
#define FINN_MAXWELL_PROFILER_DEVICE_RESERVED_INTERFACE_ID (0xb2cc00U)
typedef FINN_RM_API FINN_MAXWELL_PROFILER_DEVICE_RESERVED;

#define FINN_MAXWELL_SEC2_SEC2_INTERFACE_ID (0xb6b901U)
typedef FINN_RM_API FINN_MAXWELL_SEC2_SEC2;
#define FINN_PASCAL_CHANNEL_GPFIFO_A_RESERVED_INTERFACE_ID (0xc06f00U)
typedef FINN_RM_API FINN_PASCAL_CHANNEL_GPFIFO_A_RESERVED;
#define FINN_GP100_SUBDEVICE_GRAPHICS_RESERVED_INTERFACE_ID (0xc0e000U)
typedef FINN_RM_API FINN_GP100_SUBDEVICE_GRAPHICS_RESERVED;
#define FINN_GP100_SUBDEVICE_GRAPHICS_GRAPHICS_INTERFACE_ID (0xc0e001U)
typedef FINN_RM_API FINN_GP100_SUBDEVICE_GRAPHICS_GRAPHICS;
#define FINN_GP100_SUBDEVICE_FB_RESERVED_INTERFACE_ID (0xc0e100U)
typedef FINN_RM_API FINN_GP100_SUBDEVICE_FB_RESERVED;
#define FINN_GP100_SUBDEVICE_FB_FB_INTERFACE_ID (0xc0e101U)
typedef FINN_RM_API FINN_GP100_SUBDEVICE_FB_FB;
#define FINN_VOLTA_GSP_GSP_INTERFACE_ID (0xc31001U)
typedef FINN_RM_API FINN_VOLTA_GSP_GSP;
#define FINN_ACCESS_COUNTER_NOTIFY_BUFFER_RESERVED_INTERFACE_ID (0xc36500U)
typedef FINN_RM_API FINN_ACCESS_COUNTER_NOTIFY_BUFFER_RESERVED;
#define FINN_ACCESS_COUNTER_NOTIFY_BUFFER_ACCESS_CNTR_BUFFER_INTERFACE_ID (0xc36501U)
typedef FINN_RM_API FINN_ACCESS_COUNTER_NOTIFY_BUFFER_ACCESS_CNTR_BUFFER;
#define FINN_MMU_FAULT_BUFFER_RESERVED_INTERFACE_ID (0xc36900U)
typedef FINN_RM_API FINN_MMU_FAULT_BUFFER_RESERVED;
#define FINN_MMU_FAULT_BUFFER_MMU_FAULT_BUFFER_INTERFACE_ID (0xc36901U)
typedef FINN_RM_API FINN_MMU_FAULT_BUFFER_MMU_FAULT_BUFFER;
#define FINN_VOLTA_CHANNEL_GPFIFO_A_RESERVED_INTERFACE_ID (0xc36f00U)
typedef FINN_RM_API FINN_VOLTA_CHANNEL_GPFIFO_A_RESERVED;
#define FINN_VOLTA_CHANNEL_GPFIFO_A_GPFIFO_INTERFACE_ID (0xc36f01U)
typedef FINN_RM_API FINN_VOLTA_CHANNEL_GPFIFO_A_GPFIFO;
#define FINN_VOLTA_CHANNEL_GPFIFO_A_INTERNAL_INTERFACE_ID (0xc36f03U)
typedef FINN_RM_API FINN_VOLTA_CHANNEL_GPFIFO_A_INTERNAL;
#define FINN_NVC370_DISPLAY_RESERVED_INTERFACE_ID (0xc37000U)
typedef FINN_RM_API FINN_NVC370_DISPLAY_RESERVED;
#define FINN_NVC370_DISPLAY_CHNCTL_INTERFACE_ID (0xc37001U)
typedef FINN_RM_API FINN_NVC370_DISPLAY_CHNCTL;
#define FINN_NVC370_DISPLAY_EVENT_INTERFACE_ID (0xc37009U)
typedef FINN_RM_API FINN_NVC370_DISPLAY_EVENT;
#define FINN_NVC370_DISPLAY_OR_INTERFACE_ID (0xc37004U)
typedef FINN_RM_API FINN_NVC370_DISPLAY_OR;
#define FINN_NVC370_DISPLAY_RG_INTERFACE_ID (0xc37002U)
typedef FINN_RM_API FINN_NVC370_DISPLAY_RG;
#define FINN_NVC370_DISPLAY_VERIF_INTERFACE_ID (0xc37006U)
typedef FINN_RM_API FINN_NVC370_DISPLAY_VERIF;
#define FINN_NVC372_DISPLAY_SW_RESERVED_INTERFACE_ID (0xc37200U)
typedef FINN_RM_API FINN_NVC372_DISPLAY_SW_RESERVED;
#define FINN_NVC372_DISPLAY_SW_CHNCTL_INTERFACE_ID (0xc37201U)
typedef FINN_RM_API FINN_NVC372_DISPLAY_SW_CHNCTL;

#define FINN_GV100_SUBDEVICE_GRAPHICS_RESERVED_INTERFACE_ID (0xc3e000U)
typedef FINN_RM_API FINN_GV100_SUBDEVICE_GRAPHICS_RESERVED;
#define FINN_GV100_SUBDEVICE_GRAPHICS_GRAPHICS_INTERFACE_ID (0xc3e001U)
typedef FINN_RM_API FINN_GV100_SUBDEVICE_GRAPHICS_GRAPHICS;
#define FINN_GV100_SUBDEVICE_FB_RESERVED_INTERFACE_ID (0xc3e100U)
typedef FINN_RM_API FINN_GV100_SUBDEVICE_FB_RESERVED;
#define FINN_GV100_SUBDEVICE_FB_FB_INTERFACE_ID (0xc3e101U)
typedef FINN_RM_API FINN_GV100_SUBDEVICE_FB_FB;
#define FINN_TURING_CHANNEL_GPFIFO_A_RESERVED_INTERFACE_ID (0xc46f00U)
typedef FINN_RM_API FINN_TURING_CHANNEL_GPFIFO_A_RESERVED;
#define FINN_AMPERE_CHANNEL_GPFIFO_A_RESERVED_INTERFACE_ID (0xc56f00U)
typedef FINN_RM_API FINN_AMPERE_CHANNEL_GPFIFO_A_RESERVED;
#define FINN_AMPERE_CHANNEL_GPFIFO_A_GPFIFO_INTERFACE_ID (0xc56f01U)
typedef FINN_RM_API FINN_AMPERE_CHANNEL_GPFIFO_A_GPFIFO;
#define FINN_AMPERE_SMC_PARTITION_REF_RESERVED_INTERFACE_ID (0xc63700U)
typedef FINN_RM_API FINN_AMPERE_SMC_PARTITION_REF_RESERVED;
#define FINN_AMPERE_SMC_PARTITION_REF_EXEC_PARTITIONS_INTERFACE_ID (0xc63701U)
typedef FINN_RM_API FINN_AMPERE_SMC_PARTITION_REF_EXEC_PARTITIONS;
#define FINN_AMPERE_SMC_EXEC_PARTITION_REF_RESERVED_INTERFACE_ID (0xc63800U)
typedef FINN_RM_API FINN_AMPERE_SMC_EXEC_PARTITION_REF_RESERVED;
#define FINN_AMPERE_SMC_EXEC_PARTITION_REF_EXEC_PARTITION_INTERFACE_ID (0xc63801U)
typedef FINN_RM_API FINN_AMPERE_SMC_EXEC_PARTITION_REF_EXEC_PARTITION;
#define FINN_MMU_VIDMEM_ACCESS_BIT_BUFFER_RESERVED_INTERFACE_ID (0xc76300U)
typedef FINN_RM_API FINN_MMU_VIDMEM_ACCESS_BIT_BUFFER_RESERVED;
#define FINN_MMU_VIDMEM_ACCESS_BIT_BUFFER_VIDMEM_ACCESS_BIT_BUFFER_INTERFACE_ID (0xc76301U)
typedef FINN_RM_API FINN_MMU_VIDMEM_ACCESS_BIT_BUFFER_VIDMEM_ACCESS_BIT_BUFFER;
#define FINN_HOPPER_CHANNEL_GPFIFO_A_RESERVED_INTERFACE_ID (0xc86f00U)
typedef FINN_RM_API FINN_HOPPER_CHANNEL_GPFIFO_A_RESERVED;
#define FINN_BLACKWELL_CHANNEL_GPFIFO_A_RESERVED_INTERFACE_ID (0xc96f00U)
typedef FINN_RM_API FINN_BLACKWELL_CHANNEL_GPFIFO_A_RESERVED;
#define FINN_BLACKWELL_CHANNEL_GPFIFO_B_RESERVED_INTERFACE_ID (0xca6f00U)
typedef FINN_RM_API FINN_BLACKWELL_CHANNEL_GPFIFO_B_RESERVED;

#define FINN_NV_CONFIDENTIAL_COMPUTE_RESERVED_INTERFACE_ID (0xcb3300U)
typedef FINN_RM_API FINN_NV_CONFIDENTIAL_COMPUTE_RESERVED;
#define FINN_NV_CONFIDENTIAL_COMPUTE_CONF_COMPUTE_INTERFACE_ID (0xcb3301U)
typedef FINN_RM_API FINN_NV_CONFIDENTIAL_COMPUTE_CONF_COMPUTE;

#define FINN_NV_COUNTER_COLLECTION_UNIT_RESERVED_INTERFACE_ID (0xcbca00U)
typedef FINN_RM_API FINN_NV_COUNTER_COLLECTION_UNIT_RESERVED;
#define FINN_NV_COUNTER_COLLECTION_UNIT_CCU_INTERFACE_ID (0xcbca01U)
typedef FINN_RM_API FINN_NV_COUNTER_COLLECTION_UNIT_CCU;
#define FINN_NV_SCHEDULER_RESERVED_INTERFACE_ID (0xcbcb00U)
typedef FINN_RM_API FINN_NV_SCHEDULER_RESERVED;
#define FINN_NV_SCHEDULER_SCHEDULER_INTERFACE_ID (0xcbcb01U)
typedef FINN_RM_API FINN_NV_SCHEDULER_SCHEDULER;
#define FINN_NVE2_SYNCPOINT_BASE_RESERVED_INTERFACE_ID (0xe2ad00U)
typedef FINN_RM_API FINN_NVE2_SYNCPOINT_BASE_RESERVED;
#define FINN_NVE2_SYNCPOINT_BASE_SYNCPOINT_BASE_INTERFACE_ID (0xe2ad01U)
typedef FINN_RM_API FINN_NVE2_SYNCPOINT_BASE_SYNCPOINT_BASE;
