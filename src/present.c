#include <stdint.h>
#include "./present/PresentECB.c"

void present_encode(uint32_t v[2], uint32_t k[4]) {
    present128ECB_encrypt(v, 64, k);
}

void present_decode(uint32_t v[2], uint32_t k[4]) {
    present128ECB_decrypt(v, 64, k)
}
