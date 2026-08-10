/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:49:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/10 18:49:50 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	release_dongles(t_coder *coder, t_dongle *dongles)
{
	int		first_dongle;
	int		second_dongle;
	long	now;

	first_dongle = coder->id - 1;
	second_dongle = coder->id;
	if (coder->id == coder->set->number_of_coders)
		second_dongle = 0;
	now = get_time();
	pthread_mutex_lock(&dongles[first_dongle].lock_sch);
	dongles[first_dongle].available_time = now + coder->set->dongle_cooldown;
	dongles[first_dongle].first_coder = NULL;
	dongles[first_dongle].second_coder = NULL;
	pthread_mutex_unlock(&dongles[first_dongle].lock_sch);
	pthread_mutex_lock(&dongles[second_dongle].lock_sch);
	dongles[second_dongle].available_time = now + coder->set->dongle_cooldown;
	dongles[second_dongle].first_coder = NULL;
	dongles[second_dongle].second_coder = NULL;
	pthread_mutex_unlock(&dongles[second_dongle].lock_sch);
	pthread_mutex_unlock(&dongles[first_dongle].lock_d);
	pthread_mutex_unlock(&dongles[second_dongle].lock_d);
}

void	*routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->set->number_of_coders == 1)
	{
		pthread_mutex_lock(&coder->dongles[0].lock_d);
		print_m(coder, 1);
		pthread_mutex_unlock(&coder->dongles[0].lock_d);
		while (!is_stopped(coder->set))
			usleep(1000);
		return (NULL);
	}
	if (coder->id % 2 == 0)
		usleep(100);
	while (is_stopped(coder->set) != 1)
	{
		take_dongles(coder, coder->dongles);
		compile(coder);
		release_dongles(coder, coder->dongles);
		debug(coder);
		refactor(coder);
		if (coder->compile_count >= coder->set->number_of_compiles_required)
			break ;
	}
	return (NULL);
}
