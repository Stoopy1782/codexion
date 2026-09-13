/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:49:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/09/12 17:15:00 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	release_dongles(t_coder *coder, t_dongle *dongles)
{
	int	first;
	int	second;

	first = coder->id - 1;
	second = coder->id;
	if (coder->id == coder->set->number_of_coders)
		second = 0;
	release_one_dongle(coder, &dongles[first], 1);
	release_one_dongle(coder, &dongles[second], 1);
}

int	take_dongles(t_coder *coder, t_dongle *dongles)
{
	int	first;
	int	second;

	first = coder->id - 1;
	second = coder->id;
	if (coder->id == coder->set->number_of_coders)
		second = 0;
	if (first > second)
	{
		first = second;
		second = coder->id - 1;
	}
	if (acquire_dongle(coder, &dongles[first]) != 0)
		return (1);
	if (acquire_dongle(coder, &dongles[second]) != 0)
	{
		release_one_dongle(coder, &dongles[first], 0);
		return (1);
	}
	return (0);
}

static int	check_compile_limit(t_coder *coder)
{
	int	count;

	pthread_mutex_lock(&coder->lock_c);
	count = coder->compile_count;
	pthread_mutex_unlock(&coder->lock_c);
	return (count >= coder->set->number_of_compiles_required);
}

static void	*single_coder(t_coder *coder)
{
	acquire_dongle(coder, &coder->dongles[0]);
	while (!is_stopped(coder->set))
		usleep(1000);
	release_one_dongle(coder, &coder->dongles[0], 0);
	return (NULL);
}

void	*routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->set->number_of_coders == 1)
		return (single_coder(coder));
	if (coder->id % 2 == 0)
		usleep(1000);
	while (is_stopped(coder->set) != 1)
	{
		if (take_dongles(coder, coder->dongles) != 0)
			break ;
		compile(coder);
		release_dongles(coder, coder->dongles);
		debug(coder);
		refactor(coder);
		if (check_compile_limit(coder))
			break ;
	}
	return (NULL);
}
