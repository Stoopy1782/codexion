/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 17:21:26 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/03 18:36:08 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_stopped(t_set *set)
{
	int	status;

	pthread_mutex_lock(&set->lock_stop);
	status = set->is_stopped;
	pthread_mutex_unlock(&set->lock_stop);
	return (status);
}

int	check_burnout(t_coder *coders, t_set *set)
{
	int		i;
	long	last_compile;

	i = 0;
	while (i < set->number_of_coders)
	{
		pthread_mutex_lock(&coders[i].lock_c);
		last_compile = coders[i].last_compile;
		pthread_mutex_unlock(&coders[i].lock_c);
		if (get_time() - last_compile > set->time_to_burnout)
		{
			pthread_mutex_lock(&set->lock_stop);
			set->is_stopped = 1;
			pthread_mutex_unlock(&set->lock_stop);
			print_m(&coders[i], 5);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_finnished(t_coder *coders, t_set *set)
{
	int	i;
	int	count;

	i = 0;
	while (i < set->number_of_coders)
	{
		pthread_mutex_lock(&coders[i].lock_c);
		count = coders[i].compile_count;
		pthread_mutex_unlock(&coders[i].lock_c);
		if (count < set->number_of_compiles_required)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_coder	*coders;
	t_set	*set;

	coders = (t_coder *)arg;
	set = coders[0].set;
	while (is_stopped(set) != 1)
	{
		if (check_burnout(coders, set) == 1)
			return (NULL);
		if (check_finnished(coders, set) == 1)
		{
			pthread_mutex_lock(&set->lock_stop);
			set->is_stopped = 1;
			pthread_mutex_unlock(&set->lock_stop);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
