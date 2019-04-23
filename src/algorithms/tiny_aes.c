#include <stdint.h>
#include "../../lib/tiny_aes.c"

#include "../utils.c"
#include "../params.h"

//void tiny_aes_encode(uint8_t v[16], uint8_t k[16]) {
//    struct AES_ctx ctx;
//
//    AES_init_ctx(&ctx, k);
//    AES_ECB_encrypt(&ctx, v);
//}
//
//void tiny_aes_decode(uint8_t v[16], uint8_t k[16]) {
//    struct AES_ctx ctx;
//
//    AES_init_ctx(&ctx, k);
//    AES_ECB_decrypt(&ctx, v);
//}

uint64_t test_tiny_aes(uint8_t texts[], uint8_t const key[16]) {
    struct timespec mt1, mt2;
    uint64_t tt = 0;

    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);

    int p = 0;
    for (int sx = 0; sx < TEST_TRIALS_COUNT; sx++) {
        if (p >= TEST_SAMPLES_COUNT - 1) {
            p = 0;
        }

        uint8_t enc_text[16];
        uint8_t dec_text[16];
        memcpy(enc_text, &texts[p], BLOCK_SIZE_BITS / BYTE_SIZE);
        memcpy(dec_text, &texts[p + 1], BLOCK_SIZE_BITS / BYTE_SIZE);

        clock_gettime(CLOCK_REALTIME, &mt1);

        AES_ECB_encrypt(&ctx, enc_text);
        AES_ECB_decrypt(&ctx, dec_text);
        AES_ECB_decrypt(&ctx, dec_text);
        AES_ECB_encrypt(&ctx, enc_text);

        clock_gettime(CLOCK_REALTIME, &mt2);

        tt += get_time_diff(mt1, mt2);
        p++;
    }

    return tt;
}
