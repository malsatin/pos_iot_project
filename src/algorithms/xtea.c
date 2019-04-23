#include <stdint.h>
#include "../../lib/xtea.c"

#include "../utils.c"
#include "../params.h"

#define NUM_ROUNDS 32

void xtea_encode(uint32_t v[2], uint32_t const key[4]) {
    return encipher(NUM_ROUNDS, v, key);
}

void xtea_decode(uint32_t v[2], uint32_t const key[4]) {
    return decipher(NUM_ROUNDS, v, key);
}

uint64_t test_xtea(uint8_t texts[], uint8_t const key[16]) {
    printf("XTEA \n");

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

        xtea_encode(enc_text, key_prep);
        xtea_decode(dec_text, key_prep);
        xtea_decode(enc_text, key_prep);
        xtea_encode(dec_text, key_prep);

        clock_gettime(CLOCK_REALTIME, &mt2);

        tt += get_time_diff(mt1, mt2);
        p++;
    }

    return tt;
}

