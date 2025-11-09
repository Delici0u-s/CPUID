#include <stdio.h>
#include <cpuid.h>
#include <string.h>

#define DE_CPUID_BASE_IMPLEMENTATION
#include <de_CPUID_base.h>
#include <de_CPUID.h>

/* _inp = (u32)1 => 00000000000000000000000000000001 */
void print_u32_bin(u32 _inp) {
  for (usize i = 32; i-- > 0;) {
    putchar((_inp >> i) & 1 ? '1' : '0');
  }
  putchar('\n');
}
void print_u64_bin(u64 _inp) {
  for (usize i = 64; i-- > 0;) {
    putchar((_inp >> i) & 1 ? '1' : '0');
  }
  putchar('\n');
}
void print_u32_char(u32 _inp) {
  for (usize i = 4; i-- > 0;) {
    putchar((_inp >> (8 * i)) & 0xFF);
  }
  putchar('\n');
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
  de_Cos_max_iax_manufacturer_ID _m;
  de_CPUID_max_IAX_manufacturer_ID(&_m);
  de_CPUID_max_IAX_manufacturer_ID_print(&_m);

  de_Cos_pi__ft_bits _s;
  de_CPUID__pi__ft_bits(&_s);
  de_CPUID__pi__ft_bits_print(&_s);

  // printf("%d\n", _s.processor_version_information.processor_type);
  return 0;

  de_Cos_max_iax_manufacturer_ID man;
  de_CPUID_max_IAX_manufacturer_ID(&man);
  puts(man.manufacturer_ID);
  printf("%u\n", man.max_CPUID_EAX);
  return 0;

  de_cpuid_regs i;
  // de_cpuid_call_(DE_CIAX___EX_FT_2, &i);

  de_cpuid_request(DE_CIAX__MAX_IAX__MANUFAC_ID, &i);
  print_regs(i);
  print_regs_char(i);

  return 0;
}
