#include "utils.h"

void parse(int number_of_coders, int time_to_burnout, int time_to_compile, int time_to_debug, 
    int time_to_refactor, int number_of_compiles_required, int dongle_cooldown, char *scheduler){
		if (number_of_coders <= 0)
			printf("Number of coders must take natural number\n");
		if (time_to_burnout <= 0)
			printf("Time to burnout must take natural number\n");
		if (time_to_compile <= 0)
			printf("Time to compile must take natural number\n");
		if (time_to_debug <= 0)
			printf("Time to debug must take natural number\n");
		if (time_to_refactor <= 0)
			printf("Time to refactor must take natural number\n");
		if (number_of_compiles_required <= 0)
			printf("Number of compiles required must take natural number\n");
		if (dongle_cooldown <= 0)
			printf("Dongle cooldown required must take natural number\n");

		if (strcmp(scheduler, "fifo") == 0)
			printf("Do FIFO\n");
		else if (strcmp(scheduler, "edf") == 0)
			printf("Do EDF\n");
		else
			printf("Scheduler is invalid. Use 'edf' or 'fifo'\n");
		return ;
	}
