#ifndef DE_CPUID_HEADER
#define DE_CPUID_HEADER
#ifdef __cplusplus
extern "C" {
#endif

#include <common.h>

/*
to get function definitions #define DE_CPUID_IMPLEMENTATION before the #include
*/

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
DE_CPUID_API bool de_cpuid_call(u32 _op, de_cpuid_regs* _regs);

/* clang-format on */
#ifdef __cplusplus
} // extern "C"
#endif

#endif

// #define DE_CPUID_IMPLEMENTATION_DEVELOPMENT
#if defined(DE_CPUID_IMPLEMENTATION) || defined(DE_CPUID_IMPLEMENTATION_DEVELOPMENT)
#ifndef DE_CPUID_IMPLEMENTATION_INTERNAL
#define DE_CPUID_IMPLEMENTATION_INTERNAL
#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#ifndef DE_CPUID_MEMCPY
#define DE_CPUID_MEMCPY memcpy
#endif

/* implementations */
DE_CPUID_INTERNAL bool de_cpuid_call(u32 _op, de_cpuid_regs *_regs) {}

#ifdef __cplusplus
} // extern "C"
#endif
#endif
#endif
#endif
