#include <stdint.h>
#include "./lib/aes.c"

void tiny_aes_encode(uint8_t v[16], uint8_t k[16]) {
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, k);
    AES_ECB_encrypt(&ctx, v);
}

void tiny_aes_decode(uint8_t v[16], uint8_t k[16]) {
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, k);
    AES_ECB_decrypt(&ctx, v);
}


