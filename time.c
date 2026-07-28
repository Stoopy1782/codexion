#include "utils.h"


int get_time()
{
    struct timeval time1;
    struct timeval time2;
    int spent_time;

    gettimeofday(&time1, NULL);
	sleep(1);
    gettimeofday(&time2, NULL);
    spent_time = time2.tv_usec - time1.tv_usec;
    return (spent_time);
}
