#include <stdint.h>
#include <gcrypt.h>

#include "../utils.c"
#include "../params.h"

void blowfish_encrypt(unsigned char *v, gcry_cipher_hd_t *hd) {
    gcry_cipher_encrypt(*hd, v, BLOCK_SIZE_BYTES, v, BLOCK_SIZE_BYTES);
}

void blowfish_decrypt(unsigned char *v, gcry_cipher_hd_t *hd) {
    gcry_cipher_decrypt(*hd, v, BLOCK_SIZE_BYTES, v, BLOCK_SIZE_BYTES);
}

uint64_t test_blowfish(uint8_t texts[], uint8_t const key[16]) {
    printf("Blowfish \n");

    struct timespec mt1, mt2;
    uint64_t tt = 0;

    gcry_error_t gcryError;
    gcry_cipher_hd_t hd;

    gcryError = gcry_cipher_open(&hd, GCRY_CIPHER_BLOWFISH, GCRY_CIPHER_MODE_ECB, GCRY_CIPHER_CBC_CTS);

    if (gcryError) {
        printf("gcry_cipher_open failed:  %s/%s\n", gcry_strsource(gcryError), gcry_strerror(gcryError));
        return 0;
    }

    gcryError = gcry_cipher_setkey(hd, key, KEY_SIZE_BYTES);
    if (gcryError) {
        printf("gcry_cipher_setkey failed:  %s/%s\n", gcry_strsource(gcryError), gcry_strerror(gcryError));
    }

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

        blowfish_encrypt(enc_text, &hd);
        blowfish_decrypt(dec_text, &hd);
        blowfish_decrypt(dec_text, &hd);
        blowfish_encrypt(enc_text, &hd);

        clock_gettime(CLOCK_REALTIME, &mt2);

        tt += get_time_diff(mt1, mt2);
        p++;
    }

    gcry_cipher_close(hd);

    return tt;
}
