#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

// #include "src/tea.c"
// #include "src/raiden.c"

/*extern uint64_t rdtsc(void) {
    uint32_t lo, hi;

    __asm__ __volatile__ (
    "xorl %%eax,%%eax \n cpuid"
    :: :"%rax", "%rbx", "%rcx", "%rdx"
    );

    __asm__ __volatile__ ("rdtsc":"=a" (lo), "=d" (hi));

    return (uint64_t) hi << 32 | lo;
}
int main() {
    uint64_t a = rdtsc();
    uint64_t b = rdtsc();

    printf("%lld\n", a);
    printf("%lld\n", b);
    printf("%lld\n", b - a);
}*/

#define TEST_SAMPLES_COUNT 100 * 1000
#define TEST_TRIALS_COUNT 20 * 1000 * 1000
#define BLOCK_SIZE_BITS 64
#define KEY_SIZE_BITS 128
#define BYTE_SIZE 8

long get_time_diff(struct timespec start, struct timespec end) {
    return 10e9 * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
}

/*uint64_t test_empty(uint8_t texts[], uint8_t const key[16]) {
    struct timespec mt1, mt2;
    uint64_t tt = 0;

    uint32_t key_prep[4];
    memcpy(key_prep, key, KEY_SIZE_BITS / BYTE_SIZE);

    int p = 0;
    for (int sx = 0; sx < TEST_TRIALS_COUNT; sx++) {
        if(p >= TEST_SAMPLES_COUNT - 1) {
            p = 0;
        }

        uint32_t enc_text[2];
        uint32_t dec_text[2];
        memcpy(enc_text, &texts[p], BLOCK_SIZE_BITS / BYTE_SIZE);
        memcpy(dec_text, &texts[p + 1], BLOCK_SIZE_BITS / BYTE_SIZE);

        clock_gettime(CLOCK_REALTIME, &mt1);
        clock_gettime(CLOCK_REALTIME, &mt2);

        tt += get_time_diff(mt1, mt2);
        p++;
    }

    return tt;
}*/

/*uint64_t test_tea(uint8_t texts[], uint8_t const key[16]) {
    struct timespec mt1, mt2;
    uint64_t tt = 0;

    uint32_t key_prep[4];
    memcpy(key_prep, key, KEY_SIZE_BITS / BYTE_SIZE);

    int p = 0;
    for (int sx = 0; sx < TEST_TRIALS_COUNT; sx++) {
        if(p >= TEST_SAMPLES_COUNT - 1) {
            p = 0;
        }

        uint32_t enc_text[2];
        uint32_t dec_text[2];
        memcpy(enc_text, &texts[p], BLOCK_SIZE_BITS / BYTE_SIZE);
        memcpy(dec_text, &texts[p + 1], BLOCK_SIZE_BITS / BYTE_SIZE);

        clock_gettime(CLOCK_REALTIME, &mt1);

        tea_encode(enc_text, key_prep);
        tea_decode(dec_text, key_prep);
        tea_decode(enc_text, key_prep);
        tea_encode(dec_text, key_prep);

        clock_gettime(CLOCK_REALTIME, &mt2);

        tt += get_time_diff(mt1, mt2);
        p++;
    }

    return tt;
}*/

/*uint64_t test_raiden(uint8_t texts[], uint8_t const key[16]) {
    struct timespec mt1, mt2;
    uint64_t tt = 0;

    uint32_t key_prep[4];
    memcpy(key_prep, key, KEY_SIZE_BITS / BYTE_SIZE);

    int p = 0;
    for (int sx = 0; sx < TEST_TRIALS_COUNT; sx++) {
        if(p >= TEST_SAMPLES_COUNT - 1) {
            p = 0;
        }

        uint32_t enc_text[2];
        uint32_t dec_text[2];
        memcpy(enc_text, &texts[p], BLOCK_SIZE_BITS / BYTE_SIZE);
        memcpy(dec_text, &texts[p + 1], BLOCK_SIZE_BITS / BYTE_SIZE);

        clock_gettime(CLOCK_REALTIME, &mt1);

        raiden_encode(enc_text, key_prep, enc_text);
        raiden_decode(dec_text, key_prep, dec_text);
        raiden_decode(enc_text, key_prep, enc_text);
        raiden_encode(dec_text, key_prep, dec_text);

        clock_gettime(CLOCK_REALTIME, &mt2);

        tt += get_time_diff(mt1, mt2);
        p++;
    }

    return tt;
}*/

int main() {
    // initialize texts with TEST_SAMPLES_COUNT + BLOCK_SIZE / uint8_t elements
    uint8_t *texts = malloc(TEST_SAMPLES_COUNT * sizeof(uint8_t) + BLOCK_SIZE_BITS);
    // fill the texts
    for (int i = 0; i < TEST_SAMPLES_COUNT + BLOCK_SIZE_BITS / sizeof(uint8_t); ++i) {
        texts[i] = rand();
    }

    uint8_t const key[] = {0x69u, 0x68u, 0xc1u, 0x22u, 0x10u, 0xc5u, 0x8au, 0xfeu,
                           0xacu, 0x4du, 0xf2u, 0x20u, 0x9bu, 0x1bu, 0x4cu, 0x67u};

    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("Start: %ld s \n", tv.tv_sec);

    uint64_t tt = (texts, key);
    printf("Time spent: %lld ns \n", (unsigned long long) tt);
    printf("Time spent: %f s \n", (double) tt / 10e9);

    gettimeofday(&tv, NULL);
    printf("End: %ld s \n", tv.tv_sec);

    return 0;
}
