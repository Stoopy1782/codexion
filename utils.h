/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 16:51:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/09/03 16:54:20 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_dongle	t_dongle;

typedef struct s_set
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	int				scheduler;
	int				is_stopped;
	int				is_finnished;
	long			start_time;
	pthread_mutex_t	lock_stop;
	pthread_mutex_t	lock_s;
}	t_set;

typedef struct s_coder
{
	int				id;
	int				compile_count;
	long			last_compile;
	int				is_burnout;
	t_dongle		*dongles;
	t_set			*set;
	pthread_t		thread;
	pthread_mutex_t	lock_c;
}	t_coder;

typedef struct s_dongle
{
	long			available_time;
	int				id;
	int				in_use;
	t_coder			*first_coder;
	t_coder			*second_coder;
	t_set			*set;
	pthread_mutex_t	lock_sch;
	pthread_cond_t	lock_start;
}	t_dongle;

long			get_time(void);
void			*routine(void *arg);
int				start_simulation(t_set *set, t_coder *coders);
t_dongle		*create_dongles(t_set *set);
t_coder			*create_coders(t_set *set, t_dongle *dongles);
void			print_m(t_coder *coder, int option);
void			compile(t_coder *coder);
void			debug(t_coder *coder);
void			refactor(t_coder *coder);
void			burn_out(t_coder *coder);
int				take_dongles(t_coder *coder, t_dongle *dongles);
void			release_dongles(t_coder *coder, t_dongle *dongles);
int				acquire_dongle(t_coder *coder, t_dongle *dongle);
void			release_one_dongle(t_coder *c, t_dongle *d, int is_used);
void			*monitor(void *arg);
void			free_all(t_set *set, t_coder *coders);
int				is_stopped(t_set *set);
struct timespec	get_abstime(long available_time);
int				safe_atoi(const char *str);

#endif
