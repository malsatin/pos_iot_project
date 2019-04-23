#include <stdint.h>

#include "../utils.c"
#include "../params.h"

uint64_t test_empty(uint8_t texts[], uint8_t const key[16]) {
    printf("Empty \n");

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
        clock_gettime(CLOCK_REALTIME, &mt2);

        tt += get_time_diff(mt1, mt2);
        p++;
    }

    return tt;
}