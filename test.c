#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "src/params.h"
#include "src/sound.c"

//#include "src/algorithms/empty.c"
//#include "src/algorithms/tea.c"
#include "src/algorithms/xtea.c"
//#include "src/algorithms/raiden.c"
//#include "src/algorithms/present.c"
//#include "src/algorithms/tiny_aes.c"
//#include "src/algorithms/blowfish.c"
//#include "src/algorithms/aes.c"

int main() {
    // initialize texts with TEST_SAMPLES_COUNT + BLOCK_SIZE / uint8_t elements
    uint8_t *texts = malloc(TEST_SAMPLES_COUNT * sizeof(uint8_t) + BLOCK_SIZE_BITS);
    // fill the texts
    for (int i = 0; i < TEST_SAMPLES_COUNT + BLOCK_SIZE_BITS / sizeof(uint8_t); ++i) {
        texts[i] = rand();
    }

    uint8_t const key[] = {0x69u, 0x68u, 0xc1u, 0x22u, 0x10u, 0xc5u, 0x8au, 0xfeu,
                           0xacu, 0x4du, 0xf2u, 0x20u, 0x9bu, 0x1bu, 0x4cu, 0x67u};

    printf("TEST_SAMPLES_COUNT: %d \n", TEST_SAMPLES_COUNT);
    printf("TEST_TRIALS_COUNT: %d \n", TEST_TRIALS_COUNT);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    long time_start = tv.tv_sec;
    printf("Start: %ld s \n", tv.tv_sec);

    uint64_t tt = test_xtea(texts, key); // Runs actual test

    printf("Time spent: %lld ns \n", (unsigned long long) tt);
    printf("Time spent: %f s \n", (double) tt / SECOND_NANOSEC);

    gettimeofday(&tv, NULL);

    long time_end = tv.tv_sec;
    printf("End: %ld s \n", tv.tv_sec);

    printf("Program run for: %ld s \n", (time_end - time_start));

    play_sound_n_times(3, 0.5);

    return 0;
}
