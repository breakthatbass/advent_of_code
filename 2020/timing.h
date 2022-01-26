/*  *
 * TIMING.H
 *
 * An ultra simple timing library
 *
 * Usage:
 *	
 *	timing t;
 *
 *	start_timing(&t);
 *	// do stuff...
 *	end_timing(&t);
 *
 *	printf("time: %f\n", t.ttime);
 *
 *	*/

#ifndef TIMING_H__
#define TIMING_H__

#include <stdlib.h>
#include <sys/time.h>

typedef struct timing {
    struct timeval stop;
    struct timeval start;
    float ttime;	// total time is stored here
} timing;


void calc_time(timing *t) {
	// not having to do all this nonsense is what makes this lib worth it
    t->ttime = (t->stop.tv_sec * 1000000.0 + 
			t->stop.tv_usec - 
			t->start.tv_sec * 
			1000000.0 - t->start.tv_usec)/1000000.0;
}

// begin timing section
void start_timing(timing *t) {
    gettimeofday(&t->start, NULL);
}

// end timing section
void end_timing(timing *t) {
    gettimeofday(&t->stop, NULL);
    calc_time(t);
}

#endif
