#ifndef SAMPLE_H
#define SAMPLE_H

#include <pthread.h>
#include <stdio.h>

void do_one_thing(int *pnum_times);
void do_another_thing(int *pnum_times);
void do_wrap_up(int one_times, int another_times);
#endif
