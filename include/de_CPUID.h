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

///////////////////////////////////////////////////////
/* Highest Function Parameter and Manufacturer ID */
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
  u8 CLFLUSH_line_size;
  u8 max_addressable_IDs_logical_processors;
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
DE_CPUID_API u0 de_CPUID__pi__ft_bits_print(de_Cos_pi__ft_bits *_s);
///////////////////////////////////////////////////////
/* Cache and TLB Descriptor Information */

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

DE_CPUID_API bool de_CPUID_max_IAX_manufacturer_ID(de_Cos_max_iax_manufacturer_ID *_s) {
  de_cpuid_regs regs = {0};
  de_cpuid_request(DE_CIAX__MAX_IAX__MANUFAC_ID, &regs);
  _s->max_CPUID_EAX = regs.EAX;
  de_mpy(_s->manufacturer_ID, &regs.EBX, &regs.EDX, &regs.ECX);
  _s->manufacturer_ID[12] = 0; /* null terminate input str */
  return regs.EAX != 0;
}
DE_CPUID_API u0 de_CPUID_max_IAX_manufacturer_ID_print(de_Cos_max_iax_manufacturer_ID *_s) {
  DE_CPUID_PRINTF("Manufacturer ID: %s\n", _s->manufacturer_ID);
  DE_CPUID_PRINTF("Max CPUID EAX: %u\n", _s->max_CPUID_EAX);
}

DE_CPUID_API bool de_CPUID__pi__ft_bits(de_Cos_pi__ft_bits *_s) {
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

static inline const char *processor_type_to_str(unsigned type) {
  static const char *strs[] = {
      [de_cpuid_processor_type_OEM] = "OEM",
      [de_cpuid_processor_type_INTEL_overdrive] = "Intel Overdrive",
      [de_cpuid_processor_type_Dual] = "Dual",
      [de_cpuid_processor_type_Reserved_value] = "UNDETERMABLE",
  };
  return strs[type < de_cpuid_processor_type_Reserved_value ? type : de_cpuid_processor_type_Reserved_value];
}

DE_CPUID_API u0 de_CPUID__pi__ft_bits_print(de_Cos_pi__ft_bits *_s) {
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
  DE_CPUID_PRINTF("CLFLUSH line size: %u\n", ai->CLFLUSH_line_size);
  DE_CPUID_PRINTF("max addressable IDs for logical processors: %u\n", ai->max_addressable_IDs_logical_processors);
  DE_CPUID_PRINTF("Local APIC ID: %u\n", ai->logical_APIC_ID);

  DE_CPUID_PRINTF("# available Feature Information #\n");
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
  de_Cos_pi__ft_bits_FI_flags fl = _s->Feature_information_bits;
  const u8 max_per_line = 5;
  u8 added = 0;
  for (u32 i = 0; i < 64; ++i) {
    if (fl & de_CPUID_BITFLAG64(i + 1)) {
      if (added == max_per_line) {
        DE_CPUID_PRINTF("\n");
        added = 0;
      }
      DE_CPUID_PRINTF("%s ", fi_flag_names[i]);
      ++added;
    }
  }
  DE_CPUID_PRINTF("\n");
}

#ifdef __cplusplus
} // extern "C"
#endif
#endif
#endif
