/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 16:51:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/07/22 17:36:07 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_dongle {
	pthread_mutex_t	mutex;
	long	available_time;
}	t_dongle;

typedef struct s_set{
    int number_of_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	number_of_compiles_required;
	int	dongle_cooldown;
	char	*scheduler;
	int	is_stopped;
	int	is_finnished;
	pthread_mutex_t	print_mutex;
}	t_set;

typedef struct s_coder {
	int	id;
	int	compile_count;
	long	last_compile;
	t_dongle	*first_dongle;
	t_dongle	*second_dongle;
	t_set	*set;
}	t_coder;

void parse(int number_of_coders, int time_to_burnout, int time_to_compile, int time_to_debug, 
    int time_to_refactor, int number_of_compiles_required, int dongle_cooldown, char *scheduler);

#endif
