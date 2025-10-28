#include <stdio.h>
#include <cpuid.h>
#include <string.h>

#include <de_CPUID.h>

/* _inp = (u32)1 => 10000000000000000000000000000000 */
void print_u32_bin(u32 _inp) {
  for (usize i = 0; i != 32; ++i) {
    printf("%c", ((_inp >> i) & (((u32)1))) == 0 ? '0' : '1');
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
  de_cpuid_regs i;
  // de_cpuid_call_(DE_CIAX___EX_FT_2, &i);
  de_cpuid_request(DE_CIAX__MAX_IAX__MANUFAC_ID, &i);
  print_regs(i);
  print_regs_char(i);

  return 0;
}
