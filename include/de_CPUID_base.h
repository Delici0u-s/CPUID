#ifndef DE_CPUID_BASE_HEADER
#define DE_CPUID_BASE_HEADER
#ifdef __cplusplus
extern "C" {
#endif

/*
to get function definitions #define DE_CPUID_BASE_IMPLEMENTATION before the #include
*/

#if !defined(__x86_64__) && !defined(__i386__)
#error this header is for x86 only
#endif

/* possible options to set before 'first' include */
#ifndef DE_CPUID_BASE_OPTIONS
#ifdef DE_CPUID_BASE_OPTIONS
#define DE_CPUID_BASE_MEMCPY /* defaults to memcpy */
#endif
#endif

#ifdef DE_CPUID_BASE_IMPLEMENTATION
#define DE_CPUID_BASE_API
#else
#define DE_CPUID_BASE_API extern
#endif

#define DE_CPUID_BASE_INTERNAL

#include <common.h>
#include <stdbool.h>
/* clang-format off */

///////////////// basic CPUID architecture 

typedef u32 de_cpuid_register;
typedef de_cpuid_register de_cpuid_reg;

/* declarations */
typedef struct{
  union{
    struct {
    de_cpuid_reg EAX;
    de_cpuid_reg EBX;
    de_cpuid_reg ECX;
    de_cpuid_reg EDX;};
de_cpuid_reg regs[4];
  };
}de_cpuid_regs;

/* returns false if the this code is not supported */
DE_CPUID_BASE_API bool de_cpuid_call(u32 _leaf, de_cpuid_regs* _regs);
/* to allow calls for sublead, refer to https://en.wikipedia.org/wiki/CPUID#EAX=7,_ECX=0:_Extended_Features for more information ECX as subleaf*/
DE_CPUID_BASE_API bool de_cpuid_call_ex(u32 _leaf, u32 _subleaf, de_cpuid_regs *_regs);

/* if 2 args select de_cpuid_call, else de_cpuid_call_ex. Basically smart cpuid_call*/
#define de_cpuid_request(...) \
DE_INTERNAL_CPUID_CALL_GET(__VA_ARGS__, de_cpuid_call_ex, de_cpuid_call, de_cpuid_call, de_cpuid_call)(__VA_ARGS__)


/* 
   CIAX for CPUID_INPUT_EAX basically meaning leaf but leaf is boring lol
   PI for Processor Information
   __ to indicate new result parameter
   FT for Feature / Features
   ID for Identification or just ID

   CI(leaf, subleaf = 0x00000000) for CPUID instruction 
*/

///////////////////////////////////////////////////////
///////////// CPUID EAX PARAMETERS ////////////////////
///////////////////////////////////////////////////////
/* Highest Function Parameter and Manufacturer ID */
#define DE_CIAX__MAX_IAX__MANUFAC_ID CI(0x00000000)

/* Processor Info and Feature Bits */
#define DE_CIAX__PI__FT_BITS CI(0x00000001)

/* Cache and TLB Descriptor Information */
#define DE_CIAX__CACHE__TLB 0x00000002

/* Processor Serial Number */
#define DE_CIAX__SERIAL_NR CI(0x00000003)

/* Cache Hierarchy and Topology */
#define DE_CIAX__CACHE_H__TOPOLOGY_INTEL CI(0x00000004)
#define DE_CIAX__CACHE_H__TOPOLOGY_AMD CI(0x8000001D)

/* Intel Thread/Core and Cache Topology */
#define DE_CIAX__CACHE_THREAD_CORE_TOPOLOGY_INTEL CI(0x0000000B)

/* MONITOR/MWAIT Features */
#define DE_CIAX__MONITOR_MWAIT_FT CI(0x00000005)

/* Thermal and Power Management */
#define DE_CIAX__THERMAL_POWER_MANAGEMENT CI(0x00000006)

/* Extended Features */
/* refer to "https://en.wikipedia.org/wiki/CPUID#EAX=7,_ECX=0:_Extended_Features" for more information*/
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX___EX_FT_0 CI(0x00000007, 0x00000000)
#define DE_CIAX___EX_FT_1 CI(0x00000007, 0x00000001)
#define DE_CIAX___EX_FT_2 CI(0x00000007, 0x00000002)

/* XSAVE Features and State Components */
#define DE_CIAX__XSAVE_FT__STATE_COMPONENTS CI(0x0000000D)

/* SGX Capabilities */
/* refer to "https://en.wikipedia.org/wiki/CPUID#EAX=12h:_SGX_Capabilities" for more information*/
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__SGX__leaf_funcs__MISCSELECT__MAX_SIZES CI(0x00000012, 0x00000000)
#define DE_CIAX__SGX__SETTABLE_BITS_SECATTRIBS          CI(0x00000012, 0x00000001)
#define DE_CIAX__SGX__ENCLAVE_PAGE_CACHE_SEC_INFO       CI(0x00000012, 0x00000002)

/* Processor Trace*/
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__PROCESSOR_TRACE CI(0x00000014, 0x0000000)

/*  CPU, TSC, Bus and Core Crystal Clock Frequencies */
/* TSC and Core Crystal frequency information */
#define DE_CIAX__TSC__CORE_CRYST_FREQ CI(0x00000015)
/* Processor and Bus specification frequencies */
#define DE_CIAX__PROCESSOR_BUS_SPEC_FREQUENCIES CI(0x00000016)

/* SoC Vendor Attribute Enumeration */
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__SOC_VENDOR_ATTRIBS CI(0x00000017, 0x0000000)

/* Intel Key Locker Features */
#define DE_CIAX__INTEL_KEY_LOCKER_FEATURES CI(0x00000019)

/* Intel AMX Tile Information */
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__INTEL_AMX_TILE_INFO CI(0x0000001D, 0x00000001)

/* Intel AMX Tile Multiplier (TMUL) Information */
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__INTEL_AMX_TMUL_INFO         CI(0x0000001E, 0x00000000)
#define DE_CIAX__INTEL_AMX_TMUL_FEATURE_INFO CI(0x0000001E, 0x00000001)

/* AVX10 Converged Vector ISA */
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__AVX10_FT CI(0x00000024)

/* Discrete AVX10 Features */
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__AVX10_DISCRETE_FT CI(0x00000024, 0x00000001)

/* XEON phi shit */
#define DE_CIAX__HIGHEST_XEON_PHI_FUNCTION CI(0x2000000)
#define DE_CIAX__HIGHEST_XEON_PHI_FT_BITS CI(0x2000001)


///////////////////////////////////////////////////////
//////////// EXTENDED CPUID EAX PARAMETERS ////////////
///////////////////////////////////////////////////////

/*  Highest Extended Function Implemented && manufacturer ID on AMD Cpu's  */
#define DE_CIAX__MAX_EIAX CI(0x80000000)

/* Extended Processor Info and Feature Bits */
#define DE_CIAX__EX_PI__FT_BITS CI(0x80000001)

/* Processor Brand String */
/* https://en.wikipedia.org/wiki/CPUID#EAX=8000'0002h,8000'0003h,8000'0004h:_Processor_Brand_String */
#define DE_CIAX__P_BRAND_STR_0 CI(0x80000002)
#define DE_CIAX__P_BRAND_STR_1 CI(0x80000003)
#define DE_CIAX__P_BRAND_STR_2 CI(0x80000004)

/* L1 Cache and TLB Identifiers */
#define DE_CIAX__L1_CACHE__TLB_ID CI(0x80000005)

/* Extended L2 Cache Features */
#define DE_CIAX__L2_CACHE_EXTENDED CI(0x80000006)

/* Processor Power Management Information and RAS Capabilities */
#define DE_CIAX__P_POWER_MANAGEMENT__RAS_CAPABILITY CI(0x80000007)

/* Virtual and Physical Address Sizes */
#define DE_CIAX__SIZE_VIRTUAL_PHYSICAL_ADDRESS CI(0x80000008)

/* SVM_FEATURES */
#define DE_CIAX__SVM_FEATURES CI(0x8000000A)

/* Encrypted Memory Capabilities */
#define DE_CIAX__ENCR_MEM_CAPABILITY CI(0x8000001F)

/* Extended Feature Identification */
#define DE_CIAX__EXT_FT_ID CI(0x80000021)

/* AMD Easeter Eggs*/
#define DE_CIAX__AMD_EASTER_EGG_0 CI(0x8FFFFFFE)
#define DE_CIAX__AMD_EASTER_EGG_1 CI(0x8FFFFFFF)

/* Highest Centaur Extended Function */
#define DE_CIAX__CENTAUR_HIGHEST_EXT_FUNC CI(0xC0000000)

/* Centaur Feature Information */
#define DE_CIAX__CENTAUR_FT_INFOR CI(0xC0000001)

/* Helper Macros */
#define DE_INTERNAL_CPUID_CALL_GET(_1, _2, _3, NAME, ...) NAME

#define CI2(leaf, subleaf) leaf, subleaf
#define CI1(leaf) CI2(leaf, 0x00000000)

#define DE_INTERNAL_CI(_1, _2, NAME, ...) NAME
#define CI(...) DE_INTERNAL_CI(__VA_ARGS__, CI2, CI1, 0)(__VA_ARGS__)


/* END Helper Macros */

/* clang-format on */
#ifdef __cplusplus
} // extern "C"
#endif

#endif

// #define DE_CPUID_BASE_IMPLEMENTATION_DEVELOPMENT
#if defined(DE_CPUID_BASE_IMPLEMENTATION) || defined(DE_CPUID_BASE_IMPLEMENTATION_DEVELOPMENT)

#ifndef DE_CPUID_BASE_IMPLEMENTATION_INTERNAL
#define DE_CPUID_BASE_IMPLEMENTATION_INTERNAL
#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdatomic.h>

#ifndef DE_CPUID_BASE_MEMCPY
#define DE_CPUID_BASE_MEMCPY memcpy
#endif

/* implementations */

// cpuid.h implementation
#ifdef __i386__
#define __cpuid(__leaf, __eax, __ebx, __ecx, __edx)                                                                    \
  __asm("cpuid" : "=a"(__eax), "=b"(__ebx), "=c"(__ecx), "=d"(__edx) : "0"(__leaf))

#define __cpuid_count(__leaf, __count, __eax, __ebx, __ecx, __edx)                                                     \
  __asm("cpuid" : "=a"(__eax), "=b"(__ebx), "=c"(__ecx), "=d"(__edx) : "0"(__leaf), "2"(__count))
#else
/* x86-64 uses %rbx as the base register, so preserve it. */
#define __cpuid(__leaf, __eax, __ebx, __ecx, __edx)                                                                    \
  __asm("  xchgq  %%rbx,%q1\n"                                                                                         \
        "  cpuid\n"                                                                                                    \
        "  xchgq  %%rbx,%q1"                                                                                           \
        : "=a"(__eax), "=r"(__ebx), "=c"(__ecx), "=d"(__edx)                                                           \
        : "0"(__leaf))

#define __cpuid_count(__leaf, __count, __eax, __ebx, __ecx, __edx)                                                     \
  __asm("  xchgq  %%rbx,%q1\n"                                                                                         \
        "  cpuid\n"                                                                                                    \
        "  xchgq  %%rbx,%q1"                                                                                           \
        : "=a"(__eax), "=r"(__ebx), "=c"(__ecx), "=d"(__edx)                                                           \
        : "0"(__leaf), "2"(__count))
#endif

DE_CPUID_BASE_INTERNAL bool de_cpuid_verify_op(u32 _op) {
  static atomic_bool inited = false;
  static u32 max_basic = 0;
  static u32 max_extended = 0;

  if (!atomic_load_explicit(&inited, memory_order_acquire)) {
    u32 a = 0, b = 0, c = 0, d = 0;

    __cpuid(0x00000000, a, b, c, d);
    max_basic = a;

    __cpuid(0x80000000, a, b, c, d);
    max_extended = a;

    atomic_store_explicit(&inited, true, memory_order_release);
  }

  return (_op <= max_basic) || (_op >= DE_CIAX__MAX_EIAX && _op <= max_extended);
}

DE_CPUID_BASE_INTERNAL bool de_cpuid_call(u32 _leaf, de_cpuid_regs *_regs) {
  if (!de_cpuid_verify_op(_leaf) || !_regs) { return false; }
  __cpuid(_leaf, _regs->EAX, _regs->EBX, _regs->ECX, _regs->EDX);
  return true;
}

DE_CPUID_BASE_INTERNAL bool de_cpuid_call_ex(u32 _leaf, u32 _subleaf, de_cpuid_regs *_regs) {
  if (!de_cpuid_verify_op(_leaf) || !_regs) { return false; }
  __cpuid_count(_leaf, _subleaf, _regs->EAX, _regs->EBX, _regs->ECX, _regs->EDX);
  return true;
}

#ifdef __cplusplus
} // extern "C"
#endif
#endif
#endif
