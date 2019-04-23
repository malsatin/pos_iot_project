
void play_sound() {
    FILE *stream = popen("aplay -q sound.wav", "w");

    if (pclose(stream) != 0) {
        printf("Failed to play beep \n");
    }
}

void play_sound_n_times(int n, double sleep) {
    long ts = (long) (sleep * 1000 * 1000 * 1000);

    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = ts;

    for (int i = 0; i < n; ++i) {
        play_sound();

        if (nanosleep(&tim, &tim2) < 0) {
            printf("Nano sleep system call failed \n");
        }
    }
}
