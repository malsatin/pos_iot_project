#include <stdint.h>

#include "../utils.c"
#include "../params.h"

void tea_encode(uint32_t v[2], uint32_t k[4]) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0, i;             /* set up */
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];   /* cache key */
    uint32_t delta = 0x9E3779B9;                           /* a key schedule constant */

    for (i = 0; i < 32; i++) {                             /* basic cycle start */
        sum += delta;
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
    }

    v[0] = v0;
    v[1] = v1;
}

void tea_decode(uint32_t v[2], uint32_t k[4]) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0xC6EF3720, i;    /* set up; sum is 32*delta */
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];   /* cache key */
    uint32_t delta = 0x9E3779B9;                           /* a key schedule constant */

    for (i = 0; i < 32; i++) {                             /* basic cycle start */
        v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        sum -= delta;
    }

    v[0] = v0;
    v[1] = v1;
}

uint64_t test_tea(uint8_t texts[], uint8_t const key[16]) {
    printf("TEA \n");

    struct timespec mt1, mt2;
    uint64_t tt = 0;

    uint32_t key_prep[4];
    memcpy(key_prep, key, KEY_SIZE_BITS / BYTE_SIZE);

    int p = 0;
    for (int sx = 0; sx < TEST_TRIALS_COUNT; sx++) {
        if (p >= TEST_SAMPLES_COUNT - 1) {
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
}
