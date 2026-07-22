#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

void parse(int number_of_coders, int time_to_burnout, int time_to_compile, int time_to_debug, 
    int time_to_refactor, int number_of_compiles_required, int dongle_cooldown, char *scheduler);

#endif
