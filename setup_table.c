/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:49:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/07/25 15:58:33 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int create_table()
{
	
}

void create_coder(int i)
{
	t_coder coder;

	coder.id = i;
	coder.compile_count = 0;
	coder.is_burnout = 0;
	coder.last_compile = 0;
}

int setup_coders(t_set set)
{
	int i;
	i = 0;
	while (i > set.number_of_coders){
		i++;
		create_coder(i);
	}
}

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


pthread_create, pthread_join, pthread_mutex_init,
pthread_mutex_lock,
pthread_mutex_unlock, pthread_mutex_destroy,
pthread_cond_init,
pthread_cond_wait, pthread_cond_timedwait,
pthread_cond_signal,
pthread_cond_broadcast, pthread_cond_destroy

