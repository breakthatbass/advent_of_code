#ifndef _TIMING_H_
#define _TIMING_H_

#include <sys/time.h>
#include <stdio.h>

#define MIL 1000000

static float ttime;
static struct timeval start, stop;

#define start_time() { \
    gettimeofday(&start, NULL); \
}

#define end_time() { \
    gettimeofday(&stop, NULL); \
    ttime = (float)(stop.tv_sec * MIL + \
			stop.tv_usec - \
			start.tv_sec * \
			MIL - start.tv_usec)/MIL; \
}

#define print_time() { \
    printf("time: %f\n", ttime); \
}

#endif