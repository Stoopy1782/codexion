/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 16:51:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/07/31 19:44:10 by ykojima          ###   ########.fr       */
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
	long start_time;
	pthread_mutex_t	lock_s;
}	t_set;


typedef struct s_dongle {
	pthread_mutex_t	lock_d;
	long	available_time;
	int	id;
	t_set *set;
}	t_dongle;

typedef struct s_coder {
	int	id;
	int	compile_count;
	long	last_compile;
	int	is_burnout;
	t_dongle	*dongles;
	t_set *set;
	pthread_t		thread;
}	t_coder;


long get_time(void);
void	*coder_routine(void *arg);
int	start_simulation(t_set *set, t_coder *coders);
t_dongle	*create_dondles(t_set *set);
t_coder	*create_coders(t_set *set, t_dongle *dongles);
#endif
