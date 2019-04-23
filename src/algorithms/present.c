#include <stdint.h>
#include "../../present/PresentECB.c"

#include "../utils.c"
#include "../params.h"

//void present_encode(unsigned char* v, unsigned char* k) {
//    present128ECB_encrypt(v, 64, k);
//}
//
//void present_decode(unsigned char* v, unsigned char* k) {
//    present128ECB_decrypt(v, 64, k);
//}

uint64_t test_present(uint8_t texts[], uint8_t const key[16]) {
    struct timespec mt1, mt2;
    uint64_t tt = 0;

    unsigned char *key_prep = malloc(KEY_SIZE_BYTES);
    memcpy(key_prep, key, KEY_SIZE_BYTES);

    int p = 0;
    for (int sx = 0; sx < TEST_TRIALS_COUNT; sx++) {
        if (p >= TEST_SAMPLES_COUNT - 1) {
            p = 0;
        }

        unsigned char *enc_text = malloc(BLOCK_SIZE_BYTES);
        unsigned char *dec_text = malloc(BLOCK_SIZE_BYTES);
        memcpy(enc_text, &texts[p], BLOCK_SIZE_BYTES);
        memcpy(dec_text, &texts[p + 1], BLOCK_SIZE_BYTES);

        clock_gettime(CLOCK_REALTIME, &mt1);

        present128ECB_encrypt(enc_text, 64, key_prep);
        present128ECB_decrypt(dec_text, 64, key_prep);
        present128ECB_decrypt(dec_text, 64, key_prep);
        present128ECB_encrypt(enc_text, 64, key_prep);

        clock_gettime(CLOCK_REALTIME, &mt2);

        tt += get_time_diff(mt1, mt2);
        p++;
    }

    return tt;
}
