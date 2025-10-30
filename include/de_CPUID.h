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
#endif
#endif

#ifdef DE_CPUID_IMPLEMENTATION
#define DE_CPUID_API
#else
#define DE_CPUID_API extern
#endif

#define DE_CPUID_INTERNAL

#include <de_CPUID_base.h>
// /* clang-format off */

/* Cos for CPUID_output_struct*/

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

// de_Cos_pi__ft_bits_feature_info_flags 0:31 are ECX, 32:63 are EDX
#define de_Cos_pi__ft_bits_feature_info_flags_sse3 de_CPUID_BITFLAG64(0)
#define de_Cos_pi__ft_bits_feature_info_flags_pclmulqdq de_CPUID_BITFLAG64(1)
#define de_Cos_pi__ft_bits_feature_info_flags_dtes64 de_CPUID_BITFLAG64(2)
#define de_Cos_pi__ft_bits_feature_info_flags_monitor de_CPUID_BITFLAG64(3)
#define de_Cos_pi__ft_bits_feature_info_flags_ds_cpl de_CPUID_BITFLAG64(4)
#define de_Cos_pi__ft_bits_feature_info_flags_vmx de_CPUID_BITFLAG64(5)
#define de_Cos_pi__ft_bits_feature_info_flags_smx de_CPUID_BITFLAG64(6)
#define de_Cos_pi__ft_bits_feature_info_flags_est de_CPUID_BITFLAG64(7)
#define de_Cos_pi__ft_bits_feature_info_flags_tm2 de_CPUID_BITFLAG64(8)
#define de_Cos_pi__ft_bits_feature_info_flags_ssse3 de_CPUID_BITFLAG64(9)
#define de_Cos_pi__ft_bits_feature_info_flags_cnxt_id de_CPUID_BITFLAG64(10)
#define de_Cos_pi__ft_bits_feature_info_flags_sdbg de_CPUID_BITFLAG64(11)
#define de_Cos_pi__ft_bits_feature_info_flags_fma de_CPUID_BITFLAG64(12)
#define de_Cos_pi__ft_bits_feature_info_flags_cx16 de_CPUID_BITFLAG64(13)
#define de_Cos_pi__ft_bits_feature_info_flags_xtpr de_CPUID_BITFLAG64(14)
#define de_Cos_pi__ft_bits_feature_info_flags_pdcm de_CPUID_BITFLAG64(15)
#define de_Cos_pi__ft_bits_feature_info_flags_reserved_ de_CPUID_BITFLAG64(16)
#define de_Cos_pi__ft_bits_feature_info_flags_pcid de_CPUID_BITFLAG64(17)
#define de_Cos_pi__ft_bits_feature_info_flags_dca de_CPUID_BITFLAG64(18)
#define de_Cos_pi__ft_bits_feature_info_flags_sse4_1 de_CPUID_BITFLAG64(19)
#define de_Cos_pi__ft_bits_feature_info_flags_sse4_2 de_CPUID_BITFLAG64(20)
#define de_Cos_pi__ft_bits_feature_info_flags_x2apic de_CPUID_BITFLAG64(21)
#define de_Cos_pi__ft_bits_feature_info_flags_movbe de_CPUID_BITFLAG64(22)
#define de_Cos_pi__ft_bits_feature_info_flags_popcnt de_CPUID_BITFLAG64(23)
#define de_Cos_pi__ft_bits_feature_info_flags_tsc_deadline de_CPUID_BITFLAG64(24)
#define de_Cos_pi__ft_bits_feature_info_flags_aes_ni de_CPUID_BITFLAG64(25)
#define de_Cos_pi__ft_bits_feature_info_flags_xsave de_CPUID_BITFLAG64(26)
#define de_Cos_pi__ft_bits_feature_info_flags_osxsave de_CPUID_BITFLAG64(27)
#define de_Cos_pi__ft_bits_feature_info_flags_avx de_CPUID_BITFLAG64(28)
#define de_Cos_pi__ft_bits_feature_info_flags_f16c de_CPUID_BITFLAG64(29)
#define de_Cos_pi__ft_bits_feature_info_flags_rdrnd de_CPUID_BITFLAG64(30)
#define de_Cos_pi__ft_bits_feature_info_flags_hypervisor de_CPUID_BITFLAG64(31)
#define de_Cos_pi__ft_bits_feature_info_flags_fpu de_CPUID_BITFLAG64(32)
#define de_Cos_pi__ft_bits_feature_info_flags_vme de_CPUID_BITFLAG64(33)
#define de_Cos_pi__ft_bits_feature_info_flags_de de_CPUID_BITFLAG64(34)
#define de_Cos_pi__ft_bits_feature_info_flags_pse de_CPUID_BITFLAG64(35)
#define de_Cos_pi__ft_bits_feature_info_flags_tsc de_CPUID_BITFLAG64(36)
#define de_Cos_pi__ft_bits_feature_info_flags_msr de_CPUID_BITFLAG64(37)
#define de_Cos_pi__ft_bits_feature_info_flags_pae de_CPUID_BITFLAG64(38)
#define de_Cos_pi__ft_bits_feature_info_flags_mce de_CPUID_BITFLAG64(39)
#define de_Cos_pi__ft_bits_feature_info_flags_cx8 de_CPUID_BITFLAG64(40)
#define de_Cos_pi__ft_bits_feature_info_flags_apic de_CPUID_BITFLAG64(41)
#define de_Cos_pi__ft_bits_feature_info_flags_reserved_mtrr_ de_CPUID_BITFLAG64(42)
#define de_Cos_pi__ft_bits_feature_info_flags_sep de_CPUID_BITFLAG64(43)
#define de_Cos_pi__ft_bits_feature_info_flags_mtrr de_CPUID_BITFLAG64(44)
#define de_Cos_pi__ft_bits_feature_info_flags_pge de_CPUID_BITFLAG64(45)
#define de_Cos_pi__ft_bits_feature_info_flags_mca de_CPUID_BITFLAG64(46)
#define de_Cos_pi__ft_bits_feature_info_flags_cmov de_CPUID_BITFLAG64(47)
#define de_Cos_pi__ft_bits_feature_info_flags_pat de_CPUID_BITFLAG64(48)
#define de_Cos_pi__ft_bits_feature_info_flags_pse_36 de_CPUID_BITFLAG64(49)
#define de_Cos_pi__ft_bits_feature_info_flags_psn de_CPUID_BITFLAG64(50)
#define de_Cos_pi__ft_bits_feature_info_flags_clfsh de_CPUID_BITFLAG64(51)
#define de_Cos_pi__ft_bits_feature_info_flags_nx de_CPUID_BITFLAG64(52)
#define de_Cos_pi__ft_bits_feature_info_flags_ds de_CPUID_BITFLAG64(53)
#define de_Cos_pi__ft_bits_feature_info_flags_acpi de_CPUID_BITFLAG64(54)
#define de_Cos_pi__ft_bits_feature_info_flags_mmx de_CPUID_BITFLAG64(55)
#define de_Cos_pi__ft_bits_feature_info_flags_fxsr de_CPUID_BITFLAG64(56)
#define de_Cos_pi__ft_bits_feature_info_flags_sse de_CPUID_BITFLAG64(57)
#define de_Cos_pi__ft_bits_feature_info_flags_sse2 de_CPUID_BITFLAG64(58)
#define de_Cos_pi__ft_bits_feature_info_flags_ss de_CPUID_BITFLAG64(59)
#define de_Cos_pi__ft_bits_feature_info_flags_htt de_CPUID_BITFLAG64(60)
#define de_Cos_pi__ft_bits_feature_info_flags_tm de_CPUID_BITFLAG64(61)
#define de_Cos_pi__ft_bits_feature_info_flags_ia64 de_CPUID_BITFLAG64(62)
#define de_Cos_pi__ft_bits_feature_info_flags_pbe de_CPUID_BITFLAG64(63)

typedef struct {
  de_Cos_pi__ft_bits_processor_version_information processor_version_information;
  de_Cos_pi__ft_bits_additional_info additional_info;
  /* bitflags with de_Cos_pi__ft_bits_feature_info_flags */
  u64 Feature_information;
} de_Cos_pi__ft_bits;

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
/* clang-format on */
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
#include <stdatomic.h>

#ifndef DE_CPUID_MEMCPY
#define DE_CPUID_MEMCPY memcpy
#endif

/* implementations */

#ifdef __cplusplus
} // extern "C"
#endif
#endif
#endif
