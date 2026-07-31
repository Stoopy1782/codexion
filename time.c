#include "utils.h"


long	get_time(void)
{
    struct timeval time;
    if (gettimeofday(&time, NULL) != 0)
        return (0);
	return ((long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

