#include <stdint.h>

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
