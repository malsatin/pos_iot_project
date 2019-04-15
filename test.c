#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//extern uint64_t rdtsc(void) {
//    uint32_t lo, hi;
//
//    __asm__ __volatile__ (
//    "xorl %%eax,%%eax \n cpuid"
//    :: :"%rax", "%rbx", "%rcx", "%rdx"
//    );
//
//    __asm__ __volatile__ ("rdtsc":"=a" (lo), "=d" (hi));
//
//    return (uint64_t) hi << 32 | lo;
//}

//int main() {
//    uint64_t a = rdtsc();
//    uint64_t b = rdtsc();
//
//    printf("%lld\n", a);
//    printf("%lld\n", b);
//    printf("%lld\n", b - a);
//}

int main() {
    uint8_t text[] = {0x01u, 0x02u, 0x00u, 0x00u,
                      0x00u, 0x00u, 0x00u, 0x00u};

    uint8_t key[] = {0x03u, 0x04u, 0x00u, 0x00u, 0x00u,
                     0x00u, 0x00u, 0x00u, 0x00u, 0x00u};

    printf("sfsfsdfsdf \n");

    return 0;
}
