/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:49:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/02 20:05:12 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	take_dongles(t_coder *coder, t_dongle *dongles)
{
	int	first_dongle;
	int	second_dongle;

	first_dongle = coder->id - 1;
	second_dongle = coder->id;
	if (coder->id == coder->set->number_of_coders)
		second_dongle = 0;
	if (first_dongle < second_dongle)
	{
		pthread_mutex_lock(&dongles[first_dongle].lock_d);
		print_m(coder, 1);
		pthread_mutex_lock(&dongles[second_dongle].lock_d);
		print_m(coder, 1);
	}
	else
	{
		pthread_mutex_lock(&dongles[second_dongle].lock_d);
		print_m(coder, 1);
		pthread_mutex_lock(&dongles[first_dongle].lock_d);
		print_m(coder, 1);
	}
}

void	release_dongles(t_coder *coder, t_dongle *dongles)
{
	int		first_dongle;
	int		second_dongle;
	long		now;

	first_dongle = coder->id - 1;
	second_dongle = coder->id;
	if (coder->id == coder->set->number_of_coders)
		second_dongle = 0;
	now = get_time();
	dongles[first_dongle].available_time = now + coder->set->dongle_cooldown;
	dongles[second_dongle].available_time = now + coder->set->dongle_cooldown;
	pthread_mutex_unlock(&dongles[first_dongle].lock_d);
	pthread_mutex_unlock(&dongles[second_dongle].lock_d);
}

void	*routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (coder->set->is_stopped != 1)
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
