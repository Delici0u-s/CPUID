#include <stdio.h>
#include <cpuid.h>
#include <string.h>

typedef struct {
  union {
    struct {
      unsigned int eax, ebx, ecx, edx;
    };
    unsigned int regs[4];
  };
} info;

int main() {
  unsigned int code = 0;
  info i;

  __cpuid(code, i.eax, i.ebx, i.ecx, i.edx);
  char name[13];
  memcpy(name, &i.ebx, 4);
  memcpy(name + 4, &i.edx, 4);
  memcpy(name + 8, &i.ecx, 4);
  name[12] = '\0';
  printf("DEVNAME: %s\n", name);
  printf("MAx EAX: %u\n", i.eax);

  return 0;
}
