#include <stdint.h>
#include <gcrypt.h>

#include "../utils.c"
#include "../params.h"

// TODO
uint64_t test_blowfish(uint8_t texts[], uint8_t const key[16]) {
    struct timespec mt1, mt2;
    uint64_t tt = 0;

    gcry_cipher_open(&hd, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_ECB, GCRY_CIPHER_BLOWFISH);

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
