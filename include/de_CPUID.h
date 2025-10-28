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
#ifdef DE_CPUID_MEMCPY /* defaults to memcpy */
#endif
#endif

#ifdef DE_CPUID_IMPLEMENTATION
#define DE_CPUID_API
#else
#define DE_CPUID_API extern
#endif

#define DE_CPUID_INTERNAL

#include <common.h>
#include <stdbool.h>
/* clang-format off */

///////////////// basic CPUID architecture 

typedef u32 de_cpuid_register;
typedef de_cpuid_register de_cpuid_reg;

/* declarations */
typedef struct{
    de_cpuid_reg EAX;
    de_cpuid_reg EBX;
    de_cpuid_reg ECX;
    de_cpuid_reg EDX;
}de_cpuid_regs;

/* returns false if the this code is not supported */
DE_CPUID_API bool de_cpuid_call(u32 _leaf, de_cpuid_regs* _regs);
/* to allow calls for sublead, refer to https://en.wikipedia.org/wiki/CPUID#EAX=7,_ECX=0:_Extended_Features for more information ECX as subleaf*/
DE_CPUID_API bool de_cpuid_call_ex(u32 _leaf, u32 _subleaf, de_cpuid_regs *_regs);

/* if 2 args select de_cpuid_call, else de_cpuid_call_ex. Basically smart cpuid_call*/
#define de_cpuid_request(...) \
DE_INTERNAL_CPUID_CALL_GET(__VA_ARGS__, de_cpuid_call_ex, de_cpuid_call, de_cpuid_call, de_cpuid_call)(__VA_ARGS__)


/* 
   CIAX for CPUID_INPUT_EAX basically meaning leaf but leaf is boring lol
   PI for Processor Information
   __ to indicate new result parameter
   FT for Feature / Features
*/

///////////////////////////////////////////////////////
///////////// CPUID EAX PARAMETERS ////////////////////
///////////////////////////////////////////////////////
/* Highest Function Parameter and Manufacturer ID */
#define DE_CIAX__MAX_IAX__MANUFAC_ID DE_CPUID_INFO(00)

/* Processor Info and Feature Bits */
#define DE_CIAX__PI__FT_BITS DE_CPUID_INFO(01)

/* Cache and TLB Descriptor Information */
#define DE_CIAX__CACHE__TLB DE_CPUID_INFO(02)

/* Processor Serial Number */
#define DE_CIAX__SERIAL_NR DE_CPUID_INFO(03)

/* Cache Hierarchy and Topology */
#define DE_CIAX__CACHE_H__TOPOLOGY_INTEL DE_CPUID_INFO(04)
#define DE_CIAX__CACHE_H__TOPOLOGY_AMD DE_CPUID_INFO_EXTENDED(1D)

/* Intel Thread/Core and Cache Topology */
#define DE_CIAX__CACHE_THREAD_CORE_TOPOLOGY_INTEL DE_CPUID_INFO(0B)

/* MONITOR/MWAIT Features */
#define DE_CIAX__MONITOR_MWAIT_FT DE_CPUID_INFO(05)

/* Thermal and Power Management */
#define DE_CIAX__THERMAL_POWER_MANAGEMENT DE_CPUID_INFO(06)

/* Extended Features */
/* refer to "https://en.wikipedia.org/wiki/CPUID#EAX=7,_ECX=0:_Extended_Features" for more information*/
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX___EX_FT_0 DE_CPUID_INFO(07), DE_CPUID_INFO(00)
#define DE_CIAX___EX_FT_1 DE_CPUID_INFO(07), DE_CPUID_INFO(01)
#define DE_CIAX___EX_FT_2 DE_CPUID_INFO(07), DE_CPUID_INFO(02)

/* XSAVE Features and State Components */
#define DE_CIAX__XSAVE_FT__STATE_COMPONENTS DE_CPUID_INFO(0D)

/* SGX Capabilities */
/* refer to "https://en.wikipedia.org/wiki/CPUID#EAX=12h:_SGX_Capabilities" for more information*/
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__SGX__leaf_funcs__MISCSELECT__MAX_SIZES DE_CPUID_INFO(12), DE_CPUID_INFO(00)
#define DE_CIAX__SGX__SETTABLE_BITS_SECATTRIBS          DE_CPUID_INFO(12), DE_CPUID_INFO(01)
#define DE_CIAX__SGX__ENCLAVE_PAGE_CACHE_SEC_INFO       DE_CPUID_INFO(12), DE_CPUID_INFO(02)

/* Processor Trace*/
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__PROCESSOR_TRACE DE_CPUID_INFO(14), DE_CPUID_INFO(0)

/*  CPU, TSC, Bus and Core Crystal Clock Frequencies */
/* TSC and Core Crystal frequency information */
#define DE_CIAX__TSC__CORE_CRYST_FREQ DE_CPUID_INFO(15)
/* Processor and Bus specification frequencies */
#define DE_CIAX__PROCESSOR_BUS_SPEC_FREQUENCIES DE_CPUID_INFO(16)

/* SoC Vendor Attribute Enumeration */
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__SOC_VENDOR_ATTRIBS DE_CPUID_INFO(17), DE_CPUID_INFO(0)

/* Intel Key Locker Features */
#define DE_CIAX__INTEL_KEY_LOCKER_FEATURES DE_CPUID_INFO(19)

/* Intel AMX Tile Information */
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__INTEL_AMX_TILE_INFO DE_CPUID_INFO(1D), DE_CPUID_INFO(01)

/* Intel AMX Tile Multiplier (TMUL) Information */
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__INTEL_AMX_TMUL_INFO         DE_CPUID_INFO(1E), DE_CPUID_INFO(00)
#define DE_CIAX__INTEL_AMX_TMUL_FEATURE_INFO DE_CPUID_INFO(1E), DE_CPUID_INFO(01)

/* AVX10 Converged Vector ISA */
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__AVX10_FT DE_CPUID_INFO(24), DE_CPUID_INFO(00)

/* Discrete AVX10 Features */
/* input as first argument in de_cpuid_call_ex or just go with de_cpuid_request*/
#define DE_CIAX__AVX10_DISCRETE_FT DE_CPUID_INFO(24), DE_CPUID_INFO(01)

#define DE_CIAX__HIGHEST_XEON_PHI_FUNCTION 0x2000000
#define DE_CIAX__HIGHEST_XEON_PHI_FT_BITS 0x2000001


///////////////////////////////////////////////////////
//////////// EXTENDED CPUID EAX PARAMETERS ////////////
///////////////////////////////////////////////////////
#define DE_CIAX__ DE_CPUID_INFO_EXTENDED()
/*  Highest Extended Function Implemented && manufacturer ID on AMD Cpu's  */
#define DE_CIAX__MAX_EIAX DE_CPUID_INFO_EXTENDED(00)

/* Extended Processor Info and Feature Bits */
#define DE_CIAX__ DE_CPUID_INFO_EXTENDED()


/* Helper Macros */
#define DE_INTERNAL_CPUID_CALL_GET(_1, _2, _3, NAME, ...) NAME

#define DE_CPUID_INFO(hex) 0x000000##hex
#define DE_CPUID_INFO_EXTENDED(hex) 0x800000##hex
/* END Helper Macros */

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

DE_CPUID_INTERNAL bool de_cpuid_verify_op(u32 _op) {
  static atomic_bool inited = false;
  static u32 max_basic = 0;
  static u32 max_extended = 0;

  if (!atomic_load_explicit(&inited, memory_order_acquire)) {
    u32 a = 0, b = 0, c = 0, d = 0;

    __cpuid(DE_CIAX__MAX_IAX__MANUFAC_ID, a, b, c, d);
    max_basic = a;

    __cpuid(DE_CIAX__MAX_EIAX, a, b, c, d);
    max_extended = a;

    atomic_store_explicit(&inited, true, memory_order_release);
  }

  return (_op <= max_basic) || (_op >= DE_CIAX__MAX_EIAX && _op <= max_extended);
}

DE_CPUID_INTERNAL bool de_cpuid_call(u32 _leaf, de_cpuid_regs *_regs) {
  if (!de_cpuid_verify_op(_leaf) || !_regs) { return false; }
  __cpuid(_leaf, _regs->EAX, _regs->EBX, _regs->ECX, _regs->EDX);
  return true;
}

DE_CPUID_INTERNAL bool de_cpuid_call_ex(u32 _leaf, u32 _subleaf, de_cpuid_regs *_regs) {
  if (!de_cpuid_verify_op(_leaf) || !_regs) { return false; }
  __cpuid_count(_leaf, _subleaf, _regs->EAX, _regs->EBX, _regs->ECX, _regs->EDX);
  return true;
}

#ifdef __cplusplus
} // extern "C"
#endif
#endif
#endif
#endif
