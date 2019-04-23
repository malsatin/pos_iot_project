#include "params.h"

long get_time_diff(struct timespec start, struct timespec end) {
    return SECOND_NANOSEC * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
}
