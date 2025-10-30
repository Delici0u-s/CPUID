#include <stdio.h>
#include <cpuid.h>
#include <string.h>

#define DE_CPUID_BASE_IMPLEMENTATION
#include <de_CPUID_base.h>
#include <de_CPUID.h>

/* _inp = (u32)1 => 10000000000000000000000000000000 */
void print_u32_bin(u32 _inp) {
  for (usize i = 0; i != 32; ++i) {
    printf("%c", ((_inp >> i) & (((u32)1))) == 0 ? '0' : '1');
  }
  puts("");
}
void print_u64_bin(u64 _inp) {
  for (usize i = 0; i != 64; ++i) {
    printf("%c", ((_inp >> i) & (((u64)1))) == 0 ? '0' : '1');
  }
  puts("");
}

void print_u32_char(u32 _inp) {
  for (usize i = 0; i != 4; ++i) {
    printf("%c", (_inp >> (8 * i)) & 0xFF);
  }
  puts("");
}

void print_regs_char(de_cpuid_regs _r) {

  printf("EAX: ");
  print_u32_char(_r.EAX);

  printf("EBX: ");
  print_u32_char(_r.EBX);

  printf("ECX: ");
  print_u32_char(_r.ECX);

  printf("EDX: ");
  print_u32_char(_r.EDX);
  puts("");
}

void print_regs(de_cpuid_regs _r) {
  printf("EAX: ");
  print_u32_bin(_r.EAX);

  printf("EBX: ");
  print_u32_bin(_r.EBX);

  printf("ECX: ");
  print_u32_bin(_r.ECX);

  printf("EDX: ");
  print_u32_bin(_r.EDX);
  puts("");
}

int main() {
  u32 a = de_Cos_pi__ft_bits_feature_info_flags_avx;
  print_u64_bin(a);
  return 1;

  de_cpuid_regs i;
  // de_cpuid_call_(DE_CIAX___EX_FT_2, &i);

  de_cpuid_request(DE_CIAX__MAX_IAX__MANUFAC_ID, &i);
  print_regs(i);
  print_regs_char(i);

  return 0;
}
