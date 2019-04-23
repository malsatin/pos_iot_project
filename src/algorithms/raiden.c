#include <stdint.h>

#include "../utils.c"
#include "../params.h"

void raiden_encode(const uint32_t key[4], const uint32_t data[2], uint32_t result[2]) {
    uint32_t b0 = data[0], b1 = data[1], k[4] = {key[0], key[1], key[2], key[3]}, sk;
    int i;

    for (i = 0; i < 16; i++) {
        sk = k[i % 4] = ((k[0] + k[1]) + ((k[2] + k[3]) ^ (k[0] << (k[2] & 0x1F))));
        b0 += ((sk + b1) << 9) ^ ((sk - b1) ^ ((sk + b1) >> 14));
        b1 += ((sk + b0) << 9) ^ ((sk - b0) ^ ((sk + b0) >> 14));
    }

    result[0] = b0;
    result[1] = b1;
}

void raiden_decode(const uint32_t key[4], const uint32_t data[2], uint32_t result[2]) {
    uint32_t b0 = data[0], b1 = data[1], k[4] = {key[0], key[1], key[2], key[3]}, subkeys[16];
    int i;

    for (i = 0; i < 16; i++) {
        // Subkeys are calculated
        k[i % 4] = ((k[0] + k[1]) + ((k[2] + k[3]) ^ (k[0] << (k[2] & 0x1F))));
        subkeys[i] = k[i % 4];
    }

    for (i = 15; i >= 0; i--) {
        // Process is applied in the inverse order
        b1 -= ((subkeys[i] + b0) << 9) ^ ((subkeys[i] - b0) ^ ((subkeys[i] + b0) >> 14));
        b0 -= ((subkeys[i] + b1) << 9) ^ ((subkeys[i] - b1) ^ ((subkeys[i] + b1) >> 14));
    }

    result[0] = b0;
    result[1] = b1;
}

uint64_t test_raiden(uint8_t texts[], uint8_t const key[16]) {
    printf("Raiden \n");

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

        raiden_encode(enc_text, key_prep, enc_text);
        raiden_decode(dec_text, key_prep, dec_text);
        raiden_decode(enc_text, key_prep, enc_text);
        raiden_encode(dec_text, key_prep, dec_text);

        clock_gettime(CLOCK_REALTIME, &mt2);

        tt += get_time_diff(mt1, mt2);
        p++;
    }

    return tt;
}
