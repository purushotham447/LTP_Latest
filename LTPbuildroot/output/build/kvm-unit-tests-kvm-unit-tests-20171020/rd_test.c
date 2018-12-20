#include <stdint.h>
int main() {
   uint16_t seed=0;
   unsigned char ok;
   asm volatile ("rdseed %0; setc %1"
                 : "=r" (seed), "=qm" (ok));
   return ok;
}
