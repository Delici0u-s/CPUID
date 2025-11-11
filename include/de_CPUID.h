#ifndef DE_CPUID_HEADER
#define DE_CPUID_HEADER
#ifdef __cplusplus
extern "C" {
#endif

/*
to get function definitions #define DE_CPUID_IMPLEMENTATION before the #include
*/

#if !defined(__x86_64__) && !defined(__i386__)
#error this header is for x86 only
#endif

/* possible options to set before 'first' include */
#ifndef DE_CPUID_OPTIONS
#ifdef DE_CPUID_OPTIONS
#define DE_CPUID_MEMCPY /* defaults to memcpy */
#define DE_CPUID_MEMCMP /* defaults to memcmp */
#define DE_CPUID_MEMSET /* defaults to memset */
#define DE_CPUID_PRINTF /* defaults to printf */
#endif
#endif

#ifdef DE_CPUID_IMPLEMENTATION
#define DE_CPUID_API
#else
#define DE_CPUID_API extern
#endif

#define DE_CPUID_INTERNAL

#include <de_CPUID_base.h>
#include <common.h>

/* Cos for CPUID_output_struct*/
/* regarding magic numbers refer to https://en.wikipedia.org/wiki/CPUID */

///////////////////////////////////////////////////////
///////////// CPUID EAX PARAMETERS ////////////////////
///////////////////////////////////////////////////////
typedef enum {
  byte,
  kilobyte,
  megabyte,
  gigabyte,
} de_cpuid_bitesize;
///////////////////////////////////////////////////////
/* Highest Function Parameter and Manufacturer ID */

#define DE_CPUID_MANUFAC_ID_AMD "AuthenticAMD"
#define DE_CPUID_MANUFAC_ID_AMD_OLD "AMDisbetter!"
#define DE_CPUID_MANUFAC_ID_INTEL "GenuineIntel"
#define DE_CPUID_MANUFAC_ID_VIA "VIA VIA VIA "
#define DE_CPUID_MANUFAC_ID_TRANSMETA "GenuineTMx86"
#define DE_CPUID_MANUFAC_ID_TRANSMETA_OLD "TransmetaCPU"
#define DE_CPUID_MANUFAC_ID_CYRIX "CyrixInstead"
#define DE_CPUID_MANUFAC_ID_CENTAUR "CentaurHauls"
#define DE_CPUID_MANUFAC_ID_NEXGEN "NexGenDriven"
#define DE_CPUID_MANUFAC_ID_UMC "UMC UMC UMC "
#define DE_CPUID_MANUFAC_ID_SIS "SiS SiS SiS "
#define DE_CPUID_MANUFAC_ID_NSC "Geode by NSC"
#define DE_CPUID_MANUFAC_ID_RISE "RiseRiseRise"
#define DE_CPUID_MANUFAC_ID_VORTEX "Vortex86 SoC"
#define DE_CPUID_MANUFAC_ID_AO486 "MiSTer AO486"
#define DE_CPUID_MANUFAC_ID_AO486_OLD "GenuineAO486"
#define DE_CPUID_MANUFAC_ID_ZHAOXIN "  Shanghai  "
#define DE_CPUID_MANUFAC_ID_HYGON "HygonGenuine"
#define DE_CPUID_MANUFAC_ID_ELBRUS "E2K MACHINE "

// Vendor strings from hypervisors.
#define DE_CPUID_MANUFAC_ID_QEMU "TCGTCGTCGTCG"
#define DE_CPUID_MANUFAC_ID_KVM " KVMKVMKVM  "
#define DE_CPUID_MANUFAC_ID_VMWARE "VMwareVMware"
#define DE_CPUID_MANUFAC_ID_VIRTUALBOX "VBoxVBoxVBox"
#define DE_CPUID_MANUFAC_ID_XEN "XenVMMXenVMM"
#define DE_CPUID_MANUFAC_ID_HYPERV "Microsoft Hv"
#define DE_CPUID_MANUFAC_ID_PARALLELS " prl hyperv "
#define DE_CPUID_MANUFAC_ID_PARALLELS_ALT " lrpepyh vr "
#define DE_CPUID_MANUFAC_ID_BHYVE "bhyve bhyve "
#define DE_CPUID_MANUFAC_ID_QNX " QNXQVMBSQG "
typedef struct {
  u32 max_CPUID_EAX;
  char manufacturer_ID[13];
} de_Cos_max_iax_manufacturer_ID;

DE_CPUID_API bool de_CPUID_max_IAX_manufacturer_ID(de_Cos_max_iax_manufacturer_ID *_s);
DE_CPUID_API u0 de_CPUID_max_IAX_manufacturer_ID_print(de_Cos_max_iax_manufacturer_ID *_s);

///////////////////////////////////////////////////////
/* Processor Info and Feature Bits */
typedef enum {
  de_cpuid_processor_type_OEM = 0b00,
  de_cpuid_processor_type_INTEL_overdrive = 0b01,
  de_cpuid_processor_type_Dual = 0b10,
  de_cpuid_processor_type_Reserved_value = 0b11, // u fucked up lmao
} de_Cos_pi__ft_bits_processor_version_information_processor_type;

typedef struct {
  u8 extended_family_id;
  u8 extended_model_id;

  /* refer to de_Cos_pi__ft_bits_processor_version_information_processor_type */
  u8 processor_type;
  u8 family_id;
  u8 model;
  u8 Stepping_ID;
} de_Cos_pi__ft_bits_processor_version_information;

typedef struct {
  u8 brand_index;
  usize CLFLUSH_line_size;
  usize max_addressable_IDs_logical_processors;
  u8 logical_APIC_ID;
} de_Cos_pi__ft_bits_additional_info;

// de_Cos_pi__ft_bits_FI_bit 0:31 are ECX, 32:63 are EDX
// use de_CPUID_BITFLAG64(bit) to get a mask for the given bit
typedef enum {
  de_Cos_pi__ft_bits_FI_bit_sse3 = 1,
  de_Cos_pi__ft_bits_FI_bit_pclmulqdq,
  de_Cos_pi__ft_bits_FI_bit_dtes64,
  de_Cos_pi__ft_bits_FI_bit_monitor,
  de_Cos_pi__ft_bits_FI_bit_ds_cpl,
  de_Cos_pi__ft_bits_FI_bit_vmx,
  de_Cos_pi__ft_bits_FI_bit_smx,
  de_Cos_pi__ft_bits_FI_bit_est,
  de_Cos_pi__ft_bits_FI_bit_tm2,
  de_Cos_pi__ft_bits_FI_bit_ssse3,
  de_Cos_pi__ft_bits_FI_bit_cnxt_id,
  de_Cos_pi__ft_bits_FI_bit_sdbg,
  de_Cos_pi__ft_bits_FI_bit_fma,
  de_Cos_pi__ft_bits_FI_bit_cx16,
  de_Cos_pi__ft_bits_FI_bit_xtpr,
  de_Cos_pi__ft_bits_FI_bit_pdcm,
  de_Cos_pi__ft_bits_FI_bit_reserved_,
  de_Cos_pi__ft_bits_FI_bit_pcid,
  de_Cos_pi__ft_bits_FI_bit_dca,
  de_Cos_pi__ft_bits_FI_bit_sse4_1,
  de_Cos_pi__ft_bits_FI_bit_sse4_2,
  de_Cos_pi__ft_bits_FI_bit_x2apic,
  de_Cos_pi__ft_bits_FI_bit_movbe,
  de_Cos_pi__ft_bits_FI_bit_popcnt,
  de_Cos_pi__ft_bits_FI_bit_tsc_deadline,
  de_Cos_pi__ft_bits_FI_bit_aes_ni,
  de_Cos_pi__ft_bits_FI_bit_xsave,
  de_Cos_pi__ft_bits_FI_bit_osxsave,
  de_Cos_pi__ft_bits_FI_bit_avx,
  de_Cos_pi__ft_bits_FI_bit_f16c,
  de_Cos_pi__ft_bits_FI_bit_rdrnd,
  de_Cos_pi__ft_bits_FI_bit_hypervisor,
  de_Cos_pi__ft_bits_FI_bit_fpu = 33,
  de_Cos_pi__ft_bits_FI_bit_vme,
  de_Cos_pi__ft_bits_FI_bit_de,
  de_Cos_pi__ft_bits_FI_bit_pse,
  de_Cos_pi__ft_bits_FI_bit_tsc,
  de_Cos_pi__ft_bits_FI_bit_msr,
  de_Cos_pi__ft_bits_FI_bit_pae,
  de_Cos_pi__ft_bits_FI_bit_mce,
  de_Cos_pi__ft_bits_FI_bit_cx8,
  de_Cos_pi__ft_bits_FI_bit_apic,
  de_Cos_pi__ft_bits_FI_bit_reserved_mtrr_,
  de_Cos_pi__ft_bits_FI_bit_sep,
  de_Cos_pi__ft_bits_FI_bit_mtrr,
  de_Cos_pi__ft_bits_FI_bit_pge,
  de_Cos_pi__ft_bits_FI_bit_mca,
  de_Cos_pi__ft_bits_FI_bit_cmov,
  de_Cos_pi__ft_bits_FI_bit_pat,
  de_Cos_pi__ft_bits_FI_bit_pse_36,
  de_Cos_pi__ft_bits_FI_bit_psn,
  de_Cos_pi__ft_bits_FI_bit_clfsh,
  de_Cos_pi__ft_bits_FI_bit_nx,
  de_Cos_pi__ft_bits_FI_bit_ds,
  de_Cos_pi__ft_bits_FI_bit_acpi,
  de_Cos_pi__ft_bits_FI_bit_mmx,
  de_Cos_pi__ft_bits_FI_bit_fxsr,
  de_Cos_pi__ft_bits_FI_bit_sse,
  de_Cos_pi__ft_bits_FI_bit_sse2,
  de_Cos_pi__ft_bits_FI_bit_ss,
  de_Cos_pi__ft_bits_FI_bit_htt,
  de_Cos_pi__ft_bits_FI_bit_tm,
  de_Cos_pi__ft_bits_FI_bit_ia64,
  de_Cos_pi__ft_bits_FI_bit_pbe = 64,
} de_Cos_pi__ft_bits_FI_flags;

typedef struct {
  de_Cos_pi__ft_bits_processor_version_information processor_version_information;
  de_Cos_pi__ft_bits_additional_info additional_info;
  /* with de_Cos_pi__ft_bits_FI_bit_xx use de_CPUID_BITFLAG64 to get a u64 bitmask for that section */
  de_Cos_pi__ft_bits_FI_flags Feature_information_bits;
} de_Cos_pi__ft_bits;

DE_CPUID_API bool de_CPUID__pi__ft_bits(de_Cos_pi__ft_bits *_s);
DE_CPUID_API const char *de_CPUID__pi__ft_bit_to_str(de_Cos_pi__ft_bits_FI_flags _s);
DE_CPUID_API const char *de_CPUID__pi__ft_bit_to_str_description(de_Cos_pi__ft_bits_FI_flags _s);
DE_CPUID_API u0 de_CPUID__pi__ft_bits_print(de_Cos_pi__ft_bits *_s);

///////////////////////////////////////////////////////
/* Cache and TLB Descriptor Information */
/*
ITLB: Instruction Translation lookaside buffer
DTLB: Data Translation lookaside buffer
L1I: L1 instruction cache
L1D: L1 data cache
L2TLB: shared TLB
*/

typedef struct {
  usize entries;
  usize page_size;
  de_cpuid_bitesize page_size_type;
  usize associativity; /* 0 -> fully */
} de_Cos_CACHE__TLB_TLB;

typedef struct {
  usize cache_line_size;
  usize page_size;
  de_cpuid_bitesize page_size_type;
  usize associativity; /* 0 -> fully */
} de_Cos_CACHE__TLB_TLB_A;

typedef struct {
  usize capacity;
  de_cpuid_bitesize capacity_type;
  usize associativity; /* 0 -> fully */
  usize cache_line_size;
  usize cache_sector_size;
} de_Cos_CACHE__TLB_CACHE;

typedef struct {
  /* μop */
  usize capacity_uop;
  de_cpuid_bitesize capacity_type;
  usize associativity; /* 0 -> fully */
} de_Cos_CACHE__TLB_TRACE_CACHE;

typedef struct {
  de_Cos_CACHE__TLB_TLB L1I;
  de_Cos_CACHE__TLB_TLB L1D;
  de_Cos_CACHE__TLB_TLB_A L1D_ALTERNATIVE;
  de_Cos_CACHE__TLB_CACHE L2;
  de_Cos_CACHE__TLB_CACHE L3;
  de_Cos_CACHE__TLB_TLB L2TLB_1;
  de_Cos_CACHE__TLB_TLB L2TLB_2;
  de_Cos_CACHE__TLB_TRACE_CACHE trace_cache;
  usize byte_prefetch;
  bool valid;
} de_Cos_CACHE__TLB;

DE_CPUID_API bool de_CPUID__CACHE__TLB(de_Cos_CACHE__TLB *_s);
DE_CPUID_API u0 de_CPUID__CACHE__TLB_print(de_Cos_CACHE__TLB *_s);
///////////////////////////////////////////////////////
/* Processor Serial Number */

///////////////////////////////////////////////////////
/* Cache Hierarchy and Topology */

///////////////////////////////////////////////////////
/* Intel Thread/Core and Cache Topology */

///////////////////////////////////////////////////////
/* MONITOR/MWAIT Features */

///////////////////////////////////////////////////////
/* Thermal and Power Management */

///////////////////////////////////////////////////////
/* Extended Features */

///////////////////////////////////////////////////////
/* XSAVE Features and State Components */

///////////////////////////////////////////////////////
/* SGX Capabilities */

///////////////////////////////////////////////////////
/* Processor Trace*/

///////////////////////////////////////////////////////
/*  CPU, TSC, Bus and Core Crystal Clock Frequencies */

/////////
/* TSC and Core Crystal frequency information */

/////////
/* Processor and Bus specification frequencies */

///////////////////////////////////////////////////////
/* SoC Vendor Attribute Enumeration */

///////////////////////////////////////////////////////
/* Intel Key Locker Features */

///////////////////////////////////////////////////////
/* Intel AMX Tile Information */

///////////////////////////////////////////////////////
/* Intel AMX Tile Multiplier (TMUL) Information */

///////////////////////////////////////////////////////
/* AVX10 Converged Vector ISA */

///////////////////////////////////////////////////////
/* Discrete AVX10 Features */

///////////////////////////////////////////////////////
/* XEON phi shit */

///////////////////////////////////////////////////////
//////////// EXTENDED CPUID EAX PARAMETERS ////////////
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
/*  Highest Extended Function Implemented && manufacturer ID on AMD Cpu's  */

///////////////////////////////////////////////////////
/* Extended Processor Info and Feature Bits */

///////////////////////////////////////////////////////
/* Processor Brand String */

///////////////////////////////////////////////////////
/* L1 Cache and TLB Identifiers */

///////////////////////////////////////////////////////
/* Extended L2 Cache Features */

///////////////////////////////////////////////////////
/* Processor Power Management Information and RAS Capabilities */

///////////////////////////////////////////////////////
/* Virtual and Physical Address Sizes */

///////////////////////////////////////////////////////
/* SVM_FEATURES */

///////////////////////////////////////////////////////
/* Encrypted Memory Capabilities */

///////////////////////////////////////////////////////
/* Extended Feature Identification */

///////////////////////////////////////////////////////
/* AMD Easeter Eggs*/

///////////////////////////////////////////////////////
/* Highest Centaur Extended Function */

///////////////////////////////////////////////////////
/* Centaur Feature Information */

/////////////////////////////////////////////
//////////// helper macros /////////////////

/* bit goes from 0 to 31 */
#define de_CPUID_BITFLAG32(x) ((u32)(1 << (x)))
/* bit goes from 0 to 63 */
#define de_CPUID_BITFLAG64(x) ((u64)(1 << (x)))

#ifdef __cplusplus
} // extern "C"
#endif

#endif

#define DE_CPUID_IMPLEMENTATION_DEVELOPMENT
#if defined(DE_CPUID_IMPLEMENTATION) || defined(DE_CPUID_IMPLEMENTATION_DEVELOPMENT)

#ifndef DE_CPUID_IMPLEMENTATION_INTERNAL
#define DE_CPUID_IMPLEMENTATION_INTERNAL
#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdio.h>
#include <de_CPUID_base.h>
#include <common.h>

#ifndef DE_CPUID_MEMCPY
#define DE_CPUID_MEMCPY memcpy
#endif

#ifndef DE_CPUID_MEMCMP
#define DE_CPUID_MEMCMP memcmp
#endif

#ifndef DE_CPUID_MEMSET
#define DE_CPUID_MEMSET memset
#endif

#ifndef DE_CPUID_PRINTF
#define DE_CPUID_PRINTF printf
#endif

/* implementations */
/* helper funcs */
u0 de_mpy_0(u0 *addr) { (u0)(addr); }
u0 de_mpy_1(u0 *addr, u0 *reg_0) { //
  DE_CPUID_MEMCPY(addr, reg_0, sizeof(de_cpuid_register));
}
u0 de_mpy_2(u0 *addr, u0 *reg_0, u0 *reg_1) {
  DE_CPUID_MEMCPY(addr, reg_0, sizeof(de_cpuid_register));
  DE_CPUID_MEMCPY((u8 *)addr + sizeof(de_cpuid_register), reg_1, sizeof(de_cpuid_register));
}
u0 de_mpy_3(u0 *addr, u0 *reg_0, u0 *reg_1, u0 *reg_2) {
  DE_CPUID_MEMCPY(addr, reg_0, sizeof(de_cpuid_register));
  DE_CPUID_MEMCPY((u8 *)addr + sizeof(de_cpuid_register), reg_1, sizeof(de_cpuid_register));
  DE_CPUID_MEMCPY((u8 *)addr + (sizeof(de_cpuid_register) * 2), reg_2, sizeof(de_cpuid_register));
}
u0 de_mpy_4(u0 *addr, u0 *reg_0, u0 *reg_1, u0 *reg_2, u0 *reg_3) {
  DE_CPUID_MEMCPY(addr, reg_0, sizeof(de_cpuid_register));
  DE_CPUID_MEMCPY((u8 *)addr + sizeof(de_cpuid_register), reg_1, sizeof(de_cpuid_register));
  DE_CPUID_MEMCPY((u8 *)addr + (sizeof(de_cpuid_register) * 2), reg_2, sizeof(de_cpuid_register));
  DE_CPUID_MEMCPY((u8 *)addr + (sizeof(de_cpuid_register) * 3), reg_3, sizeof(de_cpuid_register));
}

#define DE_INTERNAL_MPY(_0, _1, _2, _3, _4, NAME, ...) NAME
#define de_mpy(...) DE_INTERNAL_MPY(__VA_ARGS__, de_mpy_4, de_mpy_3, de_mpy_2, de_mpy_1, de_mpy_0)(__VA_ARGS__)

/* 0 ≤ first_bit ≤ last_bit ≤ 31 */
#define MSK_32(x, y) (((u32)0xFFFFFFFFu >> (31u - ((u32)(y)))) & ((u32)0xFFFFFFFFu << ((u32)(x))))

/* 0 ≤ first_bit ≤ last_bit ≤ 64  */
#define MSK_64(x, y) (((u64)0xFFFFFFFFFFFFFFFFull >> (63u - ((u64)(y)))) & ((u64)0xFFFFFFFFFFFFFFFFull << ((u64)(x))))

/* 0 ≤ first_bit ≤ last_bit ≤ 31 */
#define GM_32(reg, first_bit, last_bit) (((reg) & MSK_32((first_bit), (last_bit))) >> (first_bit))
#define GM_64(reg, first_bit, last_bit) (((reg) & MSK_64((first_bit), (last_bit))) >> (first_bit))
/* end helper funcs */

DE_CPUID_INTERNAL bool de_CPUID_max_IAX_manufacturer_ID(de_Cos_max_iax_manufacturer_ID *_s) {
  DE_CPUID_MEMSET(_s, 0, sizeof(*_s));
  de_cpuid_regs regs = {0};

  if (!de_cpuid_request(DE_CIAX__MAX_IAX__MANUFAC_ID, &regs)) { return false; }
  _s->max_CPUID_EAX = regs.EAX;
  de_mpy(_s->manufacturer_ID, &regs.EBX, &regs.EDX, &regs.ECX);
  _s->manufacturer_ID[12] = 0; /* null terminate input str */
  return regs.EAX != 0;
}

DE_CPUID_INTERNAL u0 de_CPUID_max_IAX_manufacturer_ID_print(de_Cos_max_iax_manufacturer_ID *_s) {
  DE_CPUID_PRINTF("## Highest Function Parameter and Manufacturer ID ##");
  DE_CPUID_PRINTF("Manufacturer ID: %s\n", _s->manufacturer_ID);
  DE_CPUID_PRINTF("Max CPUID EAX: %u\n", _s->max_CPUID_EAX);
}

DE_CPUID_INTERNAL bool de_CPUID__pi__ft_bits(de_Cos_pi__ft_bits *_s) {
  DE_CPUID_MEMSET(_s, 0, sizeof(*_s));
  de_cpuid_regs regs = {0};
  if (!de_cpuid_request(DE_CIAX__PI__FT_BITS, &regs)) { return false; }
  /* processor version info in EAX*/
  de_Cos_pi__ft_bits_processor_version_information *vi = &_s->processor_version_information;
  vi->Stepping_ID = GM_32(regs.EAX, 0, 3);
  vi->model = GM_32(regs.EAX, 4, 7);
  vi->family_id = GM_32(regs.EAX, 8, 11);
  vi->processor_type = GM_32(regs.EAX, 12, 13);
  vi->extended_model_id = GM_32(regs.EAX, 16, 19);
  vi->extended_family_id = GM_32(regs.EAX, 20, 27);

  /* additional info */
  de_Cos_pi__ft_bits_additional_info *ai = &_s->additional_info;
  ai->brand_index = GM_32(regs.EBX, 0, 7);
  ai->CLFLUSH_line_size = GM_32(regs.EBX, 8, 15);
  ai->max_addressable_IDs_logical_processors = GM_32(regs.EBX, 16, 23);
  ai->logical_APIC_ID = GM_32(regs.EBX, 24, 31);

  /* setting ft flags*/
  de_mpy(&_s->Feature_information_bits, &regs.ECX, &regs.EDX);
  return true;
}

DE_CPUID_INTERNAL const char *processor_type_to_str(unsigned type) {
  static const char *strs[] = {
      [de_cpuid_processor_type_OEM] = "OEM",
      [de_cpuid_processor_type_INTEL_overdrive] = "Intel Overdrive",
      [de_cpuid_processor_type_Dual] = "Dual",
      [de_cpuid_processor_type_Reserved_value] = "UNDETERMABLE",
  };
  return strs[type < de_cpuid_processor_type_Reserved_value ? type : de_cpuid_processor_type_Reserved_value];
}

DE_CPUID_INTERNAL const char *de_CPUID__pi__ft_bit_to_str(de_Cos_pi__ft_bits_FI_flags _s) {
  static const char *fi_flag_names[] = {[de_Cos_pi__ft_bits_FI_bit_sse3] = "sse3",
                                        [de_Cos_pi__ft_bits_FI_bit_pclmulqdq] = "pclmulqdq",
                                        [de_Cos_pi__ft_bits_FI_bit_dtes64] = "dtes64",
                                        [de_Cos_pi__ft_bits_FI_bit_monitor] = "monitor",
                                        [de_Cos_pi__ft_bits_FI_bit_ds_cpl] = "ds_cpl",
                                        [de_Cos_pi__ft_bits_FI_bit_vmx] = "vmx",
                                        [de_Cos_pi__ft_bits_FI_bit_smx] = "smx",
                                        [de_Cos_pi__ft_bits_FI_bit_est] = "est",
                                        [de_Cos_pi__ft_bits_FI_bit_tm2] = "tm2",
                                        [de_Cos_pi__ft_bits_FI_bit_ssse3] = "ssse3",
                                        [de_Cos_pi__ft_bits_FI_bit_cnxt_id] = "cnxt_id",
                                        [de_Cos_pi__ft_bits_FI_bit_sdbg] = "sdbg",
                                        [de_Cos_pi__ft_bits_FI_bit_fma] = "fma",
                                        [de_Cos_pi__ft_bits_FI_bit_cx16] = "cx16",
                                        [de_Cos_pi__ft_bits_FI_bit_xtpr] = "xtpr",
                                        [de_Cos_pi__ft_bits_FI_bit_pdcm] = "pdcm",
                                        [de_Cos_pi__ft_bits_FI_bit_reserved_] = "res",
                                        [de_Cos_pi__ft_bits_FI_bit_pcid] = "pcid",
                                        [de_Cos_pi__ft_bits_FI_bit_dca] = "dca",
                                        [de_Cos_pi__ft_bits_FI_bit_sse4_1] = "sse4_1",
                                        [de_Cos_pi__ft_bits_FI_bit_sse4_2] = "sse4_2",
                                        [de_Cos_pi__ft_bits_FI_bit_x2apic] = "x2apic",
                                        [de_Cos_pi__ft_bits_FI_bit_movbe] = "movbe",
                                        [de_Cos_pi__ft_bits_FI_bit_popcnt] = "popcnt",
                                        [de_Cos_pi__ft_bits_FI_bit_tsc_deadline] = "tsc_deadline",
                                        [de_Cos_pi__ft_bits_FI_bit_aes_ni] = "aes_ni",
                                        [de_Cos_pi__ft_bits_FI_bit_xsave] = "xsave",
                                        [de_Cos_pi__ft_bits_FI_bit_osxsave] = "osxsave",
                                        [de_Cos_pi__ft_bits_FI_bit_avx] = "avx",
                                        [de_Cos_pi__ft_bits_FI_bit_f16c] = "f16c",
                                        [de_Cos_pi__ft_bits_FI_bit_rdrnd] = "rdrnd",
                                        [de_Cos_pi__ft_bits_FI_bit_hypervisor] = "hypervisor",
                                        [de_Cos_pi__ft_bits_FI_bit_fpu] = "fpu",
                                        [de_Cos_pi__ft_bits_FI_bit_vme] = "vme",
                                        [de_Cos_pi__ft_bits_FI_bit_de] = "de",
                                        [de_Cos_pi__ft_bits_FI_bit_pse] = "pse",
                                        [de_Cos_pi__ft_bits_FI_bit_tsc] = "tsc",
                                        [de_Cos_pi__ft_bits_FI_bit_msr] = "msr",
                                        [de_Cos_pi__ft_bits_FI_bit_pae] = "pae",
                                        [de_Cos_pi__ft_bits_FI_bit_mce] = "mce",
                                        [de_Cos_pi__ft_bits_FI_bit_cx8] = "cx8",
                                        [de_Cos_pi__ft_bits_FI_bit_apic] = "apic",
                                        [de_Cos_pi__ft_bits_FI_bit_reserved_mtrr_] = "res_mtrr",
                                        [de_Cos_pi__ft_bits_FI_bit_sep] = "sep",
                                        [de_Cos_pi__ft_bits_FI_bit_mtrr] = "mtrr",
                                        [de_Cos_pi__ft_bits_FI_bit_pge] = "pge",
                                        [de_Cos_pi__ft_bits_FI_bit_mca] = "mca",
                                        [de_Cos_pi__ft_bits_FI_bit_cmov] = "cmov",
                                        [de_Cos_pi__ft_bits_FI_bit_pat] = "pat",
                                        [de_Cos_pi__ft_bits_FI_bit_pse_36] = "pse_36",
                                        [de_Cos_pi__ft_bits_FI_bit_psn] = "psn",
                                        [de_Cos_pi__ft_bits_FI_bit_clfsh] = "clfsh",
                                        [de_Cos_pi__ft_bits_FI_bit_nx] = "nx",
                                        [de_Cos_pi__ft_bits_FI_bit_ds] = "ds",
                                        [de_Cos_pi__ft_bits_FI_bit_acpi] = "acpi",
                                        [de_Cos_pi__ft_bits_FI_bit_mmx] = "mmx",
                                        [de_Cos_pi__ft_bits_FI_bit_fxsr] = "fxsr",
                                        [de_Cos_pi__ft_bits_FI_bit_sse] = "sse",
                                        [de_Cos_pi__ft_bits_FI_bit_sse2] = "sse2",
                                        [de_Cos_pi__ft_bits_FI_bit_ss] = "ss",
                                        [de_Cos_pi__ft_bits_FI_bit_htt] = "htt",
                                        [de_Cos_pi__ft_bits_FI_bit_tm] = "tm",
                                        [de_Cos_pi__ft_bits_FI_bit_ia64] = "ia64",
                                        [de_Cos_pi__ft_bits_FI_bit_pbe] = "pbe"};
  /*
  static const char *fi_flag_names[] = {
    "sse3",         "pclmulqdq", "dtes64",   "monitor", "ds_cpl", "vmx",    "smx",   "est",
    "tm2",          "ssse3",     "cnxt_id",  "sdbg",    "fma",    "cx16",   "xtpr",  "pdcm",
    "res",          "pcid",      "dca",      "sse4_1",  "sse4_2", "x2apic", "movbe", "popcnt",
    "tsc_deadline", "aes_ni",    "xsave",    "osxsave", "avx",    "f16c",   "rdrnd",
    "hypervisor", // 32nd entry (index 31)
    "fpu",          "vme",       "de",       "pse",     "tsc",    "msr",    "pae",   "mce",
    "cx8",          "apic",      "res_mtrr", "sep",     "mtrr",   "pge",    "mca",   "cmov",
    "pat",          "pse_36",    "psn",      "clfsh",   "nx",     "ds",     "acpi",  "mmx",
    "fxsr",         "sse",       "sse2",     "ss",      "htt",    "tm",     "ia64",  "pbe"};
    */
  return fi_flag_names[_s];
}

DE_CPUID_INTERNAL const char *de_CPUID__pi__ft_bit_to_str_description(de_Cos_pi__ft_bits_FI_flags _s) {
  static const char *fi_flag_names_ex[] = {
      [de_Cos_pi__ft_bits_FI_bit_sse3] = "SSE3 (Prescott New Instructions - PNI)",
      [de_Cos_pi__ft_bits_FI_bit_pclmulqdq] = "PCLMULQDQ (carry-less multiply) instruction",
      [de_Cos_pi__ft_bits_FI_bit_dtes64] = "64-bit debug store (EDX bit 21)",
      [de_Cos_pi__ft_bits_FI_bit_monitor] = "MONITOR and MWAIT instructions (PNI)",
      [de_Cos_pi__ft_bits_FI_bit_ds_cpl] = "CPL-qualified debug store",
      [de_Cos_pi__ft_bits_FI_bit_vmx] = "Virtual Machine eXtensions (VMX)",
      [de_Cos_pi__ft_bits_FI_bit_smx] = "Safer Mode Extensions (LaGrande) (GETSEC instruction)",
      [de_Cos_pi__ft_bits_FI_bit_est] = "Enhanced SpeedStep",
      [de_Cos_pi__ft_bits_FI_bit_tm2] = "Thermal Monitor 2",
      [de_Cos_pi__ft_bits_FI_bit_ssse3] = "Supplemental SSE3 instructions (SSSE3)",
      [de_Cos_pi__ft_bits_FI_bit_cnxt_id] = "L1 Context ID",
      [de_Cos_pi__ft_bits_FI_bit_sdbg] = "Silicon Debug interface (SDBG)",
      [de_Cos_pi__ft_bits_FI_bit_fma] = "Fused multiply-add (FMA3)",
      [de_Cos_pi__ft_bits_FI_bit_cx16] = "CMPXCHG16B instruction (CX16)",
      [de_Cos_pi__ft_bits_FI_bit_xtpr] = "Can disable sending task priority messages (XTPR)",
      [de_Cos_pi__ft_bits_FI_bit_pdcm] = "Perfmon & debug capability (PDCM)",
      [de_Cos_pi__ft_bits_FI_bit_reserved_] = "(reserved)",
      [de_Cos_pi__ft_bits_FI_bit_pcid] = "Process context identifiers (CR4 bit 17) (PCID)",
      [de_Cos_pi__ft_bits_FI_bit_dca] = "Direct cache access for DMA writes (DCA)",
      [de_Cos_pi__ft_bits_FI_bit_sse4_1] = "SSE4.1 instructions",
      [de_Cos_pi__ft_bits_FI_bit_sse4_2] = "SSE4.2 instructions",
      [de_Cos_pi__ft_bits_FI_bit_x2apic] = "x2APIC (enhanced APIC)",
      [de_Cos_pi__ft_bits_FI_bit_movbe] = "MOVBE instruction (big-endian)",
      [de_Cos_pi__ft_bits_FI_bit_popcnt] = "POPCNT instruction",
      [de_Cos_pi__ft_bits_FI_bit_tsc_deadline] = "APIC implements one-shot operation using a TSC deadline value",
      [de_Cos_pi__ft_bits_FI_bit_aes_ni] = "AES instruction set (AES-NI)",
      [de_Cos_pi__ft_bits_FI_bit_xsave] = "Extensible processor state save/restore (XSAVE/XRSTOR/XSETBV/XGETBV)",
      [de_Cos_pi__ft_bits_FI_bit_osxsave] = "XSAVE enabled by OS (OSXSAVE)",
      [de_Cos_pi__ft_bits_FI_bit_avx] = "Advanced Vector Extensions (256-bit SIMD) (AVX)",
      [de_Cos_pi__ft_bits_FI_bit_f16c] = "Floating-point conversion instructions to/from FP16 format (F16C)",
      [de_Cos_pi__ft_bits_FI_bit_rdrnd] = "RDRAND (on-chip random number generator) feature",
      [de_Cos_pi__ft_bits_FI_bit_hypervisor] = "Hypervisor present (always zero on physical CPUs)",
      [de_Cos_pi__ft_bits_FI_bit_fpu] = "Onboard x87 FPU (FPU)",
      [de_Cos_pi__ft_bits_FI_bit_vme] = "Virtual 8086 mode extensions (VME: VIF/VIP/PVI)",
      [de_Cos_pi__ft_bits_FI_bit_de] = "Debugging extensions (CR4 bit 3) (DE)",
      [de_Cos_pi__ft_bits_FI_bit_pse] = "Page Size Extension (4 MB pages) (PSE)",
      [de_Cos_pi__ft_bits_FI_bit_tsc] = "Time Stamp Counter and RDTSC instruction (TSC)",
      [de_Cos_pi__ft_bits_FI_bit_msr] = "Model-specific registers and RDMSR/WRMSR instructions (MSR)",
      [de_Cos_pi__ft_bits_FI_bit_pae] = "Physical Address Extension (PAE)",
      [de_Cos_pi__ft_bits_FI_bit_mce] = "Machine Check Exception (MCE)",
      [de_Cos_pi__ft_bits_FI_bit_cx8] = "CMPXCHG8B (compare-and-swap) instruction (CX8)",
      [de_Cos_pi__ft_bits_FI_bit_apic] = "Onboard Advanced Programmable Interrupt Controller (APIC)",
      [de_Cos_pi__ft_bits_FI_bit_reserved_mtrr_] = "(reserved)",
      [de_Cos_pi__ft_bits_FI_bit_sep] = "SYSENTER and SYSEXIT fast system call instructions (SEP)",
      [de_Cos_pi__ft_bits_FI_bit_mtrr] = "Memory Type Range Registers (MTRR)",
      [de_Cos_pi__ft_bits_FI_bit_pge] = "Page Global Enable bit in CR4 (PGE)",
      [de_Cos_pi__ft_bits_FI_bit_mca] = "Machine check architecture (MCA)",
      [de_Cos_pi__ft_bits_FI_bit_cmov] = "Conditional move: CMOV, FCMOV and FCOMI instructions (CMOV/FCMOV/FCOMI)",
      [de_Cos_pi__ft_bits_FI_bit_pat] = "Page Attribute Table (PAT)",
      [de_Cos_pi__ft_bits_FI_bit_pse_36] = "36-bit page size extension (PSE-36)",
      [de_Cos_pi__ft_bits_FI_bit_psn] = "Processor Serial Number supported and enabled (PSN)",
      [de_Cos_pi__ft_bits_FI_bit_clfsh] = "CLFLUSH cache line flush instruction (CLFLUSH)",
      [de_Cos_pi__ft_bits_FI_bit_nx] = "No-execute (NX) bit (Itanium only, reserved on other CPUs)",
      [de_Cos_pi__ft_bits_FI_bit_ds] = "Debug store: save trace of executed jumps (DS)",
      [de_Cos_pi__ft_bits_FI_bit_acpi] = "Onboard thermal control MSRs for ACPI",
      [de_Cos_pi__ft_bits_FI_bit_mmx] = "MMX instructions (64-bit SIMD)",
      [de_Cos_pi__ft_bits_FI_bit_fxsr] = "FXSAVE, FXRSTOR instructions, CR4 bit 9 (FXSR)",
      [de_Cos_pi__ft_bits_FI_bit_sse] =
          "Streaming SIMD Extensions (SSE) instructions (aka \"Katmai New Instructions\"; 128-bit SIMD)",
      [de_Cos_pi__ft_bits_FI_bit_sse2] = "SSE2 instructions",
      [de_Cos_pi__ft_bits_FI_bit_ss] = "CPU cache implements self-snoop (SS)",
      [de_Cos_pi__ft_bits_FI_bit_htt] = "Max APIC IDs reserved field is Valid (HTT)",
      [de_Cos_pi__ft_bits_FI_bit_tm] = "Thermal monitor automatically limits temperature (TM)",
      [de_Cos_pi__ft_bits_FI_bit_ia64] = "IA64 processor emulating x86 (IA64)",
      [de_Cos_pi__ft_bits_FI_bit_pbe] = "Pending Break Enable (PBE# pin) wakeup capability (PBE)"};

  return fi_flag_names_ex[_s];
}

DE_CPUID_INTERNAL u0 de_CPUID__pi__ft_bits_print(de_Cos_pi__ft_bits *_s) {
  DE_CPUID_PRINTF("## Processor Info and Feature Bits ##\n");

  DE_CPUID_PRINTF("# Processor Version Information #\n");
  de_Cos_pi__ft_bits_processor_version_information *vi = &_s->processor_version_information;
  DE_CPUID_PRINTF("Stepping ID: %u\n", vi->Stepping_ID);
  DE_CPUID_PRINTF("Model: %u\n", vi->model);
  DE_CPUID_PRINTF("Family ID: %u\n", vi->family_id);
  DE_CPUID_PRINTF("Processor Type: %s\n", processor_type_to_str(vi->processor_type));
  DE_CPUID_PRINTF("Extended Model ID: %u\n", vi->extended_model_id);
  DE_CPUID_PRINTF("Extended Family ID: %u\n", vi->extended_family_id);

  DE_CPUID_PRINTF("# Additional Information #\n");
  de_Cos_pi__ft_bits_additional_info *ai = &_s->additional_info;
  DE_CPUID_PRINTF("Brand Index: %u\n", ai->brand_index);
  DE_CPUID_PRINTF("CLFLUSH line size: %llu\n", ai->CLFLUSH_line_size);
  DE_CPUID_PRINTF("max addressable IDs for logical processors: %llu\n", ai->max_addressable_IDs_logical_processors);
  DE_CPUID_PRINTF("Local APIC ID: %u\n", ai->logical_APIC_ID);

  DE_CPUID_PRINTF("# available Feature Information #\n");
  de_Cos_pi__ft_bits_FI_flags fl = _s->Feature_information_bits;
  const u8 max_per_line = 5;
  u8 added = 0;
  for (u32 i = 0; i < 64; ++i) {
    if (fl & de_CPUID_BITFLAG64(i + 1)) {
      if (added == max_per_line) {
        DE_CPUID_PRINTF("\n");
        added = 0;
      }
      DE_CPUID_PRINTF("%s ", de_CPUID__pi__ft_bit_to_str(i + 1));
      ++added;
    }
  }
  DE_CPUID_PRINTF("\n");
}
DE_CPUID_INTERNAL u0 de_CPUID__CACHE__TLB_byte_switch(de_Cos_CACHE__TLB *_s, u8 byte) {
  switch (byte) {
  case 0x00: { /* Null descriptor: contains no information */ break;
  }
  case 0x01: { /* Instruction TLB: 4K pages, 4-way, 32 entries */
    _s->L1I.entries = 32;
    _s->L1I.page_size = 4;
    _s->L1I.page_size_type = kilobyte;
    _s->L1I.associativity = 4;
    break;
  }
  case 0x02: { /* Instruction TLB: 4M pages, fully associative, 2 entries */
    _s->L1I.entries = 2;
    _s->L1I.page_size = 4;
    _s->L1I.page_size_type = megabyte;
    _s->L1I.associativity = 0;
    break;
  }
  case 0x03: { /* Data TLB: 4K pages, 4-way, 64 entries */
    _s->L1D.entries = 64;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0x04: { /* Data TLB: 4M pages, 4-way, 8 entries */
    _s->L1D.entries = 8;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = megabyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0x05: { /* Data TLB1: 4M pages, 4-way, 32 entries */
    /* The table labels this as "Data TLB1" — treat as L1D (primary data TLB) */
    _s->L1D.entries = 32;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = megabyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0x06: {           /* 1st-level instruction cache: 8 KBytes, 4-way, 32 byte line */
    _s->L1I.entries = 0; /* Not a TLB; reuse L1I struct for L1I cache is ambiguous: we'll fill L1I cache-like fields in
                            L2/L3 not available. */
    _s->L1I.page_size = 0;
    /* Use L1I struct for TLB only. For caches use L2/L3 structs: map 1st-level instruction cache to L1I's corresponding
       "cache" fields don't exist. So store as L1I entries==0 and set L2/L3 unaffected. Alternatively store in
       L1I.page_size as capacity (kilobyte). */
    /* We'll set L1I.page_size to 8 KB so that code reading this can detect L1 instruction cache capacity */
    _s->L1I.page_size = 8;
    _s->L1I.page_size_type = kilobyte;
    _s->L1I.associativity = 4; /* 4-way */
    /* cache line size handled elsewhere (no slot in TLB struct) */
    break;
  }
  case 0x08: { /* 1st-level instruction cache: 16 KBytes, 4-way, 32 byte line */
    _s->L1I.page_size = 16;
    _s->L1I.page_size_type = kilobyte;
    _s->L1I.associativity = 4;
    break;
  }
  case 0x09: { /* 1st-level instruction cache: 32 KBytes, 4-way, 64 byte line */
    _s->L1I.page_size = 32;
    _s->L1I.page_size_type = kilobyte;
    _s->L1I.associativity = 4;
    /* store cache line in L1D.cache_line_size (best-effort) */
    _s->L1D.entries = _s->L1D.entries; /* no-op to avoid unused warning */
    break;
  }
  case 0x0A: { /* 1st-level data cache: 8 KBytes, 2-way, 32 byte line */
    _s->L1D.entries = 0;
    /* place at L1D.page_size to indicate capacity */
    _s->L1D.page_size = 8;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 2;
    break;
  }
  case 0x0B: { /* Instruction TLB: 4M pages, 4-way, 4 entries */
    _s->L1I.entries = 4;
    _s->L1I.page_size = 4;
    _s->L1I.page_size_type = megabyte;
    _s->L1I.associativity = 4;
    break;
  }
  case 0x0C: { /* 1st-level data cache: 16 KBytes, 4-way, 32 byte line */
    _s->L1D.page_size = 16;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0x0D: { /* 1st-level data cache: 16 KBytes, 4-way, 64 byte line */
    _s->L1D.page_size = 16;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 4;
    _s->L1D.entries = _s->L1D.entries; /* no-op */
    break;
  }
  case 0x0E: { /* 1st-level data cache: 24 KBytes, 6-way, 64 byte line */
    _s->L1D.page_size = 24;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 6;
    break;
  }
  case 0x1D: { /* 2nd-level cache: 128 KBytes, 2-way, 64 byte line */
    _s->L2.capacity = 128;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 2;
    _s->L2.cache_line_size = 64;
    break;
  }
  case 0x21: { /* 2nd-level cache: 256 KBytes, 8-way, 64 byte line */
    _s->L2.capacity = 256;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 8;
    _s->L2.cache_line_size = 64;
    break;
  }
  case 0x22: { /* 3rd-level cache: 512 KBytes, 4-way, 64 byte line, 2 lines per sector */
    _s->L3.capacity = 512;
    _s->L3.capacity_type = kilobyte;
    _s->L3.associativity = 4;
    _s->L3.cache_line_size = 64;
    _s->L3.cache_sector_size = 2;
    break;
  }
  case 0x23: { /* 3rd-level cache: 1 MByte, 8-way, 64 byte line, 2 lines per sector */
    _s->L3.capacity = 1;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 8;
    _s->L3.cache_line_size = 64;
    _s->L3.cache_sector_size = 2;
    break;
  }
  case 0x24: { /* 2nd-level cache: 1 MByte, 16-way, 64 byte line */
    _s->L2.capacity = 1;
    _s->L2.capacity_type = megabyte;
    _s->L2.associativity = 16;
    _s->L2.cache_line_size = 64;
    break;
  }
  case 0x25: { /* 3rd-level cache: 2 MBytes, 8-way, 64 byte line, 2 lines per sector */
    _s->L3.capacity = 2;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 8;
    _s->L3.cache_line_size = 64;
    _s->L3.cache_sector_size = 2;
    break;
  }
  case 0x29: { /* 3rd-level cache: 4 MBytes, 8-way, 64 byte line, 2 lines per sector */
    _s->L3.capacity = 4;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 8;
    _s->L3.cache_line_size = 64;
    _s->L3.cache_sector_size = 2;
    break;
  }
  case 0x2C: { /* 1st-level data cache: 32 KBytes, 8-way, 64 byte line */
    _s->L1D.page_size = 32;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 8;
    _s->L1D.entries = _s->L1D.entries; /* no-op */
    break;
  }
  case 0x30: { /* 1st-level instruction cache: 32 KBytes, 8-way, 64 byte line */
    _s->L1I.page_size = 32;
    _s->L1I.page_size_type = kilobyte;
    _s->L1I.associativity = 8;
    break;
  }
  case 0x40: { /* No 2nd-level cache or if processor contains valid 2nd-level cache, no 3rd-level cache */
    /* Set L2 and L3 capacities to 0 to indicate absent */
    _s->L2.capacity = 0;
    _s->L3.capacity = 0;
    break;
  }
  case 0x41: { /* 2nd-level cache: 128 KBytes, 4-way, 32 byte line */
    _s->L2.capacity = 128;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 4;
    _s->L2.cache_line_size = 32;
    break;
  }
  case 0x42: { /* 2nd-level cache: 256 KBytes, 4-way, 32 byte line */
    _s->L2.capacity = 256;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 4;
    _s->L2.cache_line_size = 32;
    break;
  }
  case 0x43: { /* 2nd-level cache: 512 KBytes, 4-way, 32 byte line */
    _s->L2.capacity = 512;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 4;
    _s->L2.cache_line_size = 32;
    break;
  }
  case 0x44: { /* 2nd-level cache: 1 MByte, 4-way, 32 byte line */
    _s->L2.capacity = 1;
    _s->L2.capacity_type = megabyte;
    _s->L2.associativity = 4;
    _s->L2.cache_line_size = 32;
    break;
  }
  case 0x45: { /* 2nd-level cache: 2 MByte, 4-way, 32 byte line */
    _s->L2.capacity = 2;
    _s->L2.capacity_type = megabyte;
    _s->L2.associativity = 4;
    _s->L2.cache_line_size = 32;
    break;
  }
  case 0x46: { /* 3rd-level cache: 4 MByte, 4-way, 64 byte line */
    _s->L3.capacity = 4;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 4;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0x47: { /* 3rd-level cache: 8 MByte, 8-way, 64 byte line */
    _s->L3.capacity = 8;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 8;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0x48: { /* 2nd-level cache: 3 MByte, 12-way, 64 byte line */
    _s->L2.capacity = 3;
    _s->L2.capacity_type = megabyte;
    _s->L2.associativity = 12;
    _s->L2.cache_line_size = 64;
    break;
  }
  case 0x49: { /* 3rd-level cache: 4MB, 16-way, 64 byte line (or special-case 2nd-level in some families) */
    _s->L3.capacity = 4;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 16;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0x4A: { /* 3rd-level cache: 6MByte, 12-way, 64 byte line */
    _s->L3.capacity = 6;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 12;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0x4B: { /* 3rd-level cache: 8MByte, 16-way, 64 byte line */
    _s->L3.capacity = 8;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 16;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0x4C: { /* 3rd-level cache: 12MByte, 12-way, 64 byte line */
    _s->L3.capacity = 12;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 12;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0x4D: { /* 3rd-level cache: 16MByte, 16-way, 64 byte line */
    _s->L3.capacity = 16;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 16;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0x4E: { /* 2nd-level cache: 6MByte, 24-way, 64 byte line */
    _s->L2.capacity = 6;
    _s->L2.capacity_type = megabyte;
    _s->L2.associativity = 24;
    _s->L2.cache_line_size = 64;
    break;
  }
  case 0x4F: { /* Instruction TLB: 4 KByte pages, 32 entries */
    _s->L1I.entries = 32;
    _s->L1I.page_size = 4;
    _s->L1I.page_size_type = kilobyte;
    _s->L1I.associativity = 0; /* spec lists no-way; treat as ???; keep default associativity */
    break;
  }
  case 0x50: { /* Instruction TLB: 4K and 2M/4M pages, 64 entries */
    _s->L1I.entries = 64;
    /* set to smallest page size (4K) */
    _s->L1I.page_size = 4;
    _s->L1I.page_size_type = kilobyte;
    _s->L1I.associativity = 0; /* unspecified -> leave as-is */
    break;
  }
  case 0x51: { /* Instruction TLB: 4K and 2M/4M pages, 128 entries */
    _s->L1I.entries = 128;
    _s->L1I.page_size = 4;
    _s->L1I.page_size_type = kilobyte;
    break;
  }
  case 0x52: { /* Instruction TLB: 4K and 2M/4M pages, 256 entries */
    _s->L1I.entries = 256;
    _s->L1I.page_size = 4;
    _s->L1I.page_size_type = kilobyte;
    break;
  }
  case 0x55: { /* Instruction TLB: 2M/4M pages, fully associative, 7 entries */
    _s->L1I.entries = 7;
    _s->L1I.page_size = 2;
    _s->L1I.page_size_type = megabyte;
    _s->L1I.associativity = 0;
    break;
  }
  case 0x56: { /* Data TLB0: 4 MByte pages, 4-way, 16 entries */
    _s->L1D.entries = 16;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = megabyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0x57: { /* Data TLB0: 4 KByte pages, 4-way, 16 entries */
    _s->L1D.entries = 16;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0x59: { /* Data TLB0: 4 KByte pages, fully associative, 16 entries */
    _s->L1D.entries = 16;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 0;
    break;
  }
  case 0x5A: { /* Data TLB0: 2M or 4M pages, 4-way, 32 entries */
    _s->L1D.entries = 32;
    _s->L1D.page_size = 2;
    _s->L1D.page_size_type = megabyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0x5B: { /* Data TLB: 4K and 4M pages, 64 entries */
    _s->L1D.entries = 64;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    break;
  }
  case 0x5C: { /* Data TLB: 4K and 4M pages, 128 entries */
    _s->L1D.entries = 128;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    break;
  }
  case 0x5D: { /* Data TLB: 4K and 4M pages, 256 entries */
    _s->L1D.entries = 256;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    break;
  }
  case 0x60: { /* 1st-level data cache: 16 KByte, 8-way, 64 byte line */
    _s->L1D.page_size = 16;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 8;
    _s->L1D.entries = _s->L1D.entries; /* no-op */
    break;
  }
  case 0x61: { /* Instruction TLB: 4K pages, fully associative, 48 entries */
    _s->L1I.entries = 48;
    _s->L1I.page_size = 4;
    _s->L1I.page_size_type = kilobyte;
    _s->L1I.associativity = 0;
    break;
  }
  case 0x63: { /* Data TLB: 2M/4M pages, 4-way, 32 entries + separate 1GB array 4 entries */
    _s->L1D.entries = 32;
    _s->L1D.page_size = 2;
    _s->L1D.page_size_type = megabyte;
    _s->L1D.associativity = 4;
    /* store 1GB array info in L2TLB_2 */
    _s->L2TLB_2.entries = 4;
    _s->L2TLB_2.page_size = 1;
    _s->L2TLB_2.page_size_type = gigabyte;
    _s->L2TLB_2.associativity = 4;
    break;
  }
  case 0x64: { /* Data TLB: 4 KByte pages, 4-way, 512 entries */
    _s->L1D.entries = 512;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0x66: { /* 1st-level data cache: 8 KByte, 4-way, 64 byte line */
    _s->L1D_ALTERNATIVE.page_size = 8;
    _s->L1D_ALTERNATIVE.page_size_type = kilobyte;
    _s->L1D_ALTERNATIVE.associativity = 4;
    _s->L1D_ALTERNATIVE.cache_line_size = 64;
    break;
  }
  case 0x67: { /* 1st-level data cache: 16 KByte, 4-way, 64 byte line */
    _s->L1D_ALTERNATIVE.page_size = 16;
    _s->L1D_ALTERNATIVE.page_size_type = kilobyte;
    _s->L1D_ALTERNATIVE.associativity = 4;
    _s->L1D_ALTERNATIVE.cache_line_size = 64;
    break;
  }
  case 0x68: { /* 1st-level data cache: 32 KByte, 4-way, 64 byte line */
    _s->L1D_ALTERNATIVE.page_size = 32;
    _s->L1D_ALTERNATIVE.page_size_type = kilobyte;
    _s->L1D_ALTERNATIVE.associativity = 4;
    _s->L1D_ALTERNATIVE.cache_line_size = 64;
    break;
  }
  case 0x6A: { /* uTLB: 4 KByte pages, 8-way, 64 entries */
    /* Micro-op TLB — map to trace_cache or L2TLB_1? We'll put in L2TLB_1 */
    _s->L2TLB_1.entries = 64;
    _s->L2TLB_1.page_size = 4;
    _s->L2TLB_1.page_size_type = kilobyte;
    _s->L2TLB_1.associativity = 8;
    break;
  }
  case 0x6B: { /* DTLB: 4 KByte pages, 8-way, 256 entries */
    _s->L1D.entries = 256;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 8;
    break;
  }
  case 0x6C: { /* DTLB: 2M/4M pages, 8-way, 128 entries */
    _s->L1D.entries = 128;
    _s->L1D.page_size = 2;
    _s->L1D.page_size_type = megabyte;
    _s->L1D.associativity = 8;
    break;
  }
  case 0x6D: { /* DTLB: 1 GByte pages, fully associative, 16 entries */
    _s->L1D.entries = 16;
    _s->L1D.page_size = 1;
    _s->L1D.page_size_type = gigabyte;
    _s->L1D.associativity = 0;
    break;
  }
  case 0x70: { /* Trace cache: 12 K-μop, 8-way */
    _s->trace_cache.capacity_uop = 12;
    _s->trace_cache.capacity_type = kilobyte; /* interpret K-μop as kilobyte enum for size unit */
    _s->trace_cache.associativity = 8;
    break;
  }
  case 0x71: { /* Trace cache: 16 K-μop, 8-way */
    _s->trace_cache.capacity_uop = 16;
    _s->trace_cache.capacity_type = kilobyte;
    _s->trace_cache.associativity = 8;
    break;
  }
  case 0x72: { /* Trace cache: 32 K-μop, 8-way */
    _s->trace_cache.capacity_uop = 32;
    _s->trace_cache.capacity_type = kilobyte;
    _s->trace_cache.associativity = 8;
    break;
  }
  case 0x76: { /* Instruction TLB: 2M/4M pages, fully associative, 8 entries */
    _s->L1I.entries = 8;
    _s->L1I.page_size = 2;
    _s->L1I.page_size_type = megabyte;
    _s->L1I.associativity = 0;
    break;
  }
  case 0x78: { /* 2nd-level cache: 1 MByte, 4-way, 64 byte line */
    _s->L2.capacity = 1;
    _s->L2.capacity_type = megabyte;
    _s->L2.associativity = 4;
    _s->L2.cache_line_size = 64;
    break;
  }
  case 0x79: { /* 2nd-level cache: 128 KByte, 8-way, 64 byte line, 2 lines per sector */
    _s->L2.capacity = 128;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 8;
    _s->L2.cache_line_size = 64;
    _s->L2.cache_sector_size = 2;
    break;
  }
  case 0x7A: { /* 2nd-level cache: 256 KByte, 8-way, 64 byte line, 2 lines per sector */
    _s->L2.capacity = 256;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 8;
    _s->L2.cache_line_size = 64;
    _s->L2.cache_sector_size = 2;
    break;
  }
  case 0x7B: { /* 2nd-level cache: 512 KByte, 8-way, 64 byte line, 2 lines per sector */
    _s->L2.capacity = 512;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 8;
    _s->L2.cache_line_size = 64;
    _s->L2.cache_sector_size = 2;
    break;
  }
  case 0x7C: { /* 2nd-level cache: 1 MByte, 8-way, 64 byte line, 2 lines per sector */
    _s->L2.capacity = 1;
    _s->L2.capacity_type = megabyte;
    _s->L2.associativity = 8;
    _s->L2.cache_line_size = 64;
    _s->L2.cache_sector_size = 2;
    break;
  }
  case 0x7D: { /* 2nd-level cache: 2 MByte, 8-way, 64 byte line */
    _s->L2.capacity = 2;
    _s->L2.capacity_type = megabyte;
    _s->L2.associativity = 8;
    _s->L2.cache_line_size = 64;
    break;
  }
  case 0x7F: { /* 2nd-level cache: 512 KByte, 2-way, 64 byte line */
    _s->L2.capacity = 512;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 2;
    _s->L2.cache_line_size = 64;
    break;
  }
  case 0x80: { /* 2nd-level cache: 512 KByte, 8-way, 64 byte line */
    _s->L2.capacity = 512;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 8;
    _s->L2.cache_line_size = 64;
    break;
  }
  case 0x82: { /* 2nd-level cache: 256 KByte, 8-way, 32 byte line */
    _s->L2.capacity = 256;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 8;
    _s->L2.cache_line_size = 32;
    break;
  }
  case 0x83: { /* 2nd-level cache: 512 KByte, 8-way, 32 byte line */
    _s->L2.capacity = 512;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 8;
    _s->L2.cache_line_size = 32;
    break;
  }
  case 0x84: { /* 2nd-level cache: 1 MByte, 8-way, 32 byte line */
    _s->L2.capacity = 1;
    _s->L2.capacity_type = megabyte;
    _s->L2.associativity = 8;
    _s->L2.cache_line_size = 32;
    break;
  }
  case 0x85: { /* 2nd-level cache: 2 MByte, 8-way, 32 byte line */
    _s->L2.capacity = 2;
    _s->L2.capacity_type = megabyte;
    _s->L2.associativity = 8;
    _s->L2.cache_line_size = 32;
    break;
  }
  case 0x86: { /* 2nd-level cache: 512 KByte, 4-way, 64 byte line */
    _s->L2.capacity = 512;
    _s->L2.capacity_type = kilobyte;
    _s->L2.associativity = 4;
    _s->L2.cache_line_size = 64;
    break;
  }
  case 0x87: { /* 2nd-level cache: 1 MByte, 8-way, 64 byte line */
    _s->L2.capacity = 1;
    _s->L2.capacity_type = megabyte;
    _s->L2.associativity = 8;
    _s->L2.cache_line_size = 64;
    break;
  }
  case 0xA0: { /* DTLB: 4K pages, fully associative, 32 entries */
    _s->L1D.entries = 32;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 0;
    break;
  }
  case 0xB0: { /* Instruction TLB: 4K pages, 4-way, 128 entries */
    _s->L1I.entries = 128;
    _s->L1I.page_size = 4;
    _s->L1I.page_size_type = kilobyte;
    _s->L1I.associativity = 4;
    break;
  }
  case 0xB1: {           /* Instruction TLB: 2M pages 4-way 8 entries OR 4M pages 4-way 4 entries */
    _s->L1I.entries = 8; /* choose the 2M case as primary */
    _s->L1I.page_size = 2;
    _s->L1I.page_size_type = megabyte;
    _s->L1I.associativity = 4;
    break;
  }
  case 0xB2: { /* Instruction TLB: 4K pages, 4-way, 64 entries */
    _s->L1I.entries = 64;
    _s->L1I.page_size = 4;
    _s->L1I.page_size_type = kilobyte;
    _s->L1I.associativity = 4;
    break;
  }
  case 0xB3: { /* Data TLB: 4K pages, 4-way, 128 entries */
    _s->L1D.entries = 128;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0xB4: { /* Data TLB1: 4K pages, 4-way, 256 entries */
    _s->L1D.entries = 256;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0xB5: { /* Instruction TLB: 4K pages, 8-way, 64 entries */
    _s->L1I.entries = 64;
    _s->L1I.page_size = 4;
    _s->L1I.page_size_type = kilobyte;
    _s->L1I.associativity = 8;
    break;
  }
  case 0xB6: { /* Instruction TLB: 4K pages, 8-way, 128 entries */
    _s->L1I.entries = 128;
    _s->L1I.page_size = 4;
    _s->L1I.page_size_type = kilobyte;
    _s->L1I.associativity = 8;
    break;
  }
  case 0xBA: { /* Data TLB1: 4K pages, 4-way, 64 entries */
    _s->L1D.entries = 64;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0xC0: { /* Data TLB: 4K and 4M pages, 4-way, 8 entries */
    _s->L1D.entries = 8;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0xC1: { /* STLB: Shared 2nd-Level TLB: 4K/2M, 8-way, 1024 entries */
    _s->L2TLB_1.entries = 1024;
    _s->L2TLB_1.page_size = 4; /* primary smaller page */
    _s->L2TLB_1.page_size_type = kilobyte;
    _s->L2TLB_1.associativity = 8;
    break;
  }
  case 0xC2: { /* DTLB: 4K/2M pages, 4-way, 16 entries */
    _s->L1D.entries = 16;
    _s->L1D.page_size = 4;
    _s->L1D.page_size_type = kilobyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0xC3: { /* STLB: Shared 2nd-Level TLB: 4K/2M, 6-way, 1536 entries. Also 1GB pages, 4-way, 16 entries */
    /* put the primary (4K/2M) in L2TLB_1 and the 1GB array in L2TLB_2 */
    _s->L2TLB_1.entries = 1536;
    _s->L2TLB_1.page_size = 4;
    _s->L2TLB_1.page_size_type = kilobyte;
    _s->L2TLB_1.associativity = 6;

    _s->L2TLB_2.entries = 16;
    _s->L2TLB_2.page_size = 1;
    _s->L2TLB_2.page_size_type = gigabyte;
    _s->L2TLB_2.associativity = 4;
    break;
  }
  case 0xC4: { /* DTLB: 2M/4M pages, 4-way, 32 entries */
    _s->L1D.entries = 32;
    _s->L1D.page_size = 2;
    _s->L1D.page_size_type = megabyte;
    _s->L1D.associativity = 4;
    break;
  }
  case 0xCA: { /* STLB: Shared 2nd-Level TLB: 4K pages, 4-way, 512 entries */
    _s->L2TLB_1.entries = 512;
    _s->L2TLB_1.page_size = 4;
    _s->L2TLB_1.page_size_type = kilobyte;
    _s->L2TLB_1.associativity = 4;
    break;
  }
  case 0xD0: { /* 3rd-level cache: 512 KByte, 4-way, 64 byte line */
    _s->L3.capacity = 512;
    _s->L3.capacity_type = kilobyte;
    _s->L3.associativity = 4;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xD1: { /* 3rd-level cache: 1 MByte, 4-way, 64 byte line */
    _s->L3.capacity = 1;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 4;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xD2: { /* 3rd-level cache: 2 MByte, 4-way, 64 byte line */
    _s->L3.capacity = 2;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 4;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xD6: { /* 3rd-level cache: 1 MByte, 8-way, 64 byte line */
    _s->L3.capacity = 1;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 8;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xD7: { /* 3rd-level cache: 2 MByte, 8-way, 64 byte line */
    _s->L3.capacity = 2;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 8;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xD8: { /* 3rd-level cache: 4 MByte, 8-way, 64 byte line */
    _s->L3.capacity = 4;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 8;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xDC: {              /* 3rd-level cache: 1.5 MByte, 12-way, 64 byte line */
    _s->L3.capacity = 1536; /* store KB as 1536 KB */
    _s->L3.capacity_type = kilobyte;
    _s->L3.associativity = 12;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xDD: { /* 3rd-level cache: 3 MByte, 12-way, 64 byte line */
    _s->L3.capacity = 3;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 12;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xDE: { /* 3rd-level cache: 6 MByte, 12-way, 64 byte line */
    _s->L3.capacity = 6;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 12;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xE2: { /* 3rd-level cache: 2 MByte, 16-way, 64 byte line */
    _s->L3.capacity = 2;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 16;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xE3: { /* 3rd-level cache: 4 MByte, 16-way, 64 byte line */
    _s->L3.capacity = 4;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 16;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xE4: { /* 3rd-level cache: 8 MByte, 16-way, 64 byte line */
    _s->L3.capacity = 8;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 16;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xEA: { /* 3rd-level cache: 12 MByte, 24-way, 64 byte line */
    _s->L3.capacity = 12;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 24;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xEB: { /* 3rd-level cache: 18 MByte, 24-way, 64 byte line */
    _s->L3.capacity = 18;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 24;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xEC: { /* 3rd-level cache: 24 MByte, 24-way, 64 byte line */
    _s->L3.capacity = 24;
    _s->L3.capacity_type = megabyte;
    _s->L3.associativity = 24;
    _s->L3.cache_line_size = 64;
    break;
  }
  case 0xF0: { /* Prefetch: 64-Byte prefetching */ _s->byte_prefetch = 64; break;
  }
  case 0xF1: { /* Prefetch: 128-Byte prefetching */ _s->byte_prefetch = 128; break;
  }
  case 0xFE: { /* General: CPUID leaf 2 does not report TLB descriptor information */
    /* Nothing to populate here; consumer should query leaf 0x18 */
    break;
  }
  case 0xFF: { /* General: CPUID leaf 2 does not report cache descriptor information */
    /* Nothing to populate here; consumer should query leaf 4 */
    break;
  }
  default: {
    /* Unknown descriptor — leave structure unchanged */
    break;
  }
  }
}

DE_CPUID_INTERNAL bool de_CPUID__CACHE__TLB(de_Cos_CACHE__TLB *_s) {
  DE_CPUID_MEMSET(_s, 0, sizeof(*_s));
  de_cpuid_regs regs = {0};

  /* initial request: get the AL (call_amount) and first set of regs */
  if (!de_cpuid_request(DE_CIAX__CACHE__TLB, 0, &regs)) {
    _s->valid = false;
    return false;
  }

  usize call_amount = regs.EAX & 0x000000FFU;
  if (call_amount == 0) call_amount = 1; /* be conservative */

  /* iterate calls, reuse regs for call == 0 to avoid redundant request */
  for (usize call = 0; call < call_amount; ++call) {
    if (call != 0) {
      if (!de_cpuid_request(DE_CIAX__CACHE__TLB, call, &regs)) {
        /* if a later call fails, consider result partial but valid? here we fail */
        _s->valid = false;
        return false;
      }
    }

    for (usize r = 0; r < 4; ++r) {
      u32 reg = regs.regs[r];

      /* If this is EAX (r==0) we must mask out the low 8 bits (AL) which
         hold the call_amount, not a descriptor byte. */
      if (r == 0) reg &= 0xFFFFFF00u;

      /* Intel: if MSB is 1 the whole 32-bit register contains no valid descriptors */
      if (reg & 0x80000000U) continue;

      for (usize b = 0; b < 4; ++b) {
        u8 byte = (u8)((reg >> (8 * b)) & 0xFFU);

        if (byte == 0x00) continue; /* null descriptor -> skip */

        /* record that we must consult other leaves rather than bail out */
        if (byte == 0xFF) {
          /* TODO: needs leaf 4 here for information */
          continue;
        }
        if (byte == 0xFE) {
          /* TODO: needs leaf 18 here for information */
          continue;
        }

        DE_CPUID_PRINTF("cache/tlb descriptor found: 0x%02X (reg %u byte %u)\n", byte, (unsigned)r, (unsigned)b);

        /* Normal descriptor — dispatch to your handler */
        de_CPUID__CACHE__TLB_byte_switch(_s, byte);
      }
    }
  }

  /* at this point we successfully parsed whatever leaf 2 provided */
  _s->valid = true;
  return true;
}

DE_CPUID_INTERNAL char de_CPUID_IMPL_bitesize_pref_str(de_cpuid_bitesize _s) {
  switch (_s) {
  case byte: {
    return ' ';
  }
  case kilobyte: {
    return 'K';
  }
  case megabyte: {
    return 'M';
  }
  case gigabyte: {
    return 'G';
  }
  default: {
    return '#';
  }
  }
}

DE_CPUID_INTERNAL u0 de_CPUID__CACHE__TLB__print_TLB(de_Cos_CACHE__TLB_TLB _s) {
  DE_CPUID_PRINTF("entries: %llu\n", _s.entries);
  DE_CPUID_PRINTF("page_size: %llu %cp\n", _s.page_size, de_CPUID_IMPL_bitesize_pref_str(_s.page_size_type));
  if (_s.associativity) {
    DE_CPUID_PRINTF("associativity: %llu-way\n", _s.associativity);
  } else {
    DE_CPUID_PRINTF("associativity: fully\n");
  }
}
DE_CPUID_INTERNAL u0 de_CPUID__CACHE__TLB__print_TLB_A(de_Cos_CACHE__TLB_TLB_A _s) {
  DE_CPUID_PRINTF("cache_line_size: %llu\n", _s.cache_line_size);
  DE_CPUID_PRINTF("page_size: %llu %cp\n", _s.page_size, de_CPUID_IMPL_bitesize_pref_str(_s.page_size_type));
  if (_s.associativity) {
    DE_CPUID_PRINTF("associativity: %llu-way\n", _s.associativity);
  } else {
    DE_CPUID_PRINTF("associativity: fully\n");
  }
}
DE_CPUID_INTERNAL u0 de_CPUID__CACHE__TLB__print_CACHE(de_Cos_CACHE__TLB_CACHE _s) {
  DE_CPUID_PRINTF("capacity: %llu %cB\n", _s.capacity, de_CPUID_IMPL_bitesize_pref_str(_s.capacity_type));
  DE_CPUID_PRINTF("cache_line_size: %llu B\n", _s.cache_line_size);
  DE_CPUID_PRINTF("cache_sector_size: %llu lines\n", _s.cache_sector_size);
  if (_s.associativity) {
    DE_CPUID_PRINTF("associativity: %llu-way\n", _s.associativity);
  } else {
    DE_CPUID_PRINTF("associativity: fully\n");
  }
}
DE_CPUID_INTERNAL u0 de_CPUID__CACHE__TLB__print_TRACE_CACHE(de_Cos_CACHE__TLB_TRACE_CACHE _s) {
  DE_CPUID_PRINTF("capacity: %llu %c-uop\n", _s.capacity_uop, de_CPUID_IMPL_bitesize_pref_str(_s.capacity_type));
  if (_s.associativity) {
    DE_CPUID_PRINTF("associativity: %llu-way\n", _s.associativity);
  } else {
    DE_CPUID_PRINTF("associativity: fully\n");
  }
}

DE_CPUID_INTERNAL u0 de_CPUID__CACHE__TLB_print(de_Cos_CACHE__TLB *_s) { //
  DE_CPUID_PRINTF("## Cache and TLB Descriptor Information ##\n");
  if (_s->valid) {

    if (_s->L1I.page_size != 0) {
      DE_CPUID_PRINTF("L1 Instruction Cache:\n");
      de_CPUID__CACHE__TLB__print_TLB(_s->L1I);
    }
    if (_s->L1D.page_size != 0) {
      DE_CPUID_PRINTF("L1 Data Cache:\n");
      de_CPUID__CACHE__TLB__print_TLB(_s->L1D);
    } else if (_s->L1D_ALTERNATIVE.page_size != 0) {
      DE_CPUID_PRINTF("L1 Data Cache:\n");
      de_CPUID__CACHE__TLB__print_TLB_A(_s->L1D_ALTERNATIVE);
    }
    if (_s->L2.capacity != 0) {
      DE_CPUID_PRINTF("L2 Cache:\n");
      de_CPUID__CACHE__TLB__print_CACHE(_s->L2);
    }
    if (_s->L2TLB_1.page_size != 0) {
      DE_CPUID_PRINTF("L2TLB:\n");
      de_CPUID__CACHE__TLB__print_TLB(_s->L2TLB_1);

      if (_s->L2TLB_2.page_size != 0) {
        DE_CPUID_PRINTF("L2TLB2:\n");
        de_CPUID__CACHE__TLB__print_TLB(_s->L2TLB_2);
      }
    }
    if (_s->L3.capacity != 0) {
      DE_CPUID_PRINTF("L3 Cache:\n");
      de_CPUID__CACHE__TLB__print_CACHE(_s->L3);
    }
    if (_s->trace_cache.capacity_uop != 0) {
      DE_CPUID_PRINTF("trace_cache:\n");
      de_CPUID__CACHE__TLB__print_TRACE_CACHE(_s->trace_cache);
    }
    DE_CPUID_PRINTF("Byte prefetch: %llu\n", _s->byte_prefetch);
  } else {
    DE_CPUID_PRINTF("extracted Information is invalid");
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
#endif
#endif
