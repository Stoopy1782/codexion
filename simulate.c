/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 17:21:26 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/03 15:06:03 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_last_compile(t_set *set, t_coder *coders)
{
	int	i;

	i = 0;
	while (i < set->number_of_coders)
	{
		coders[i].last_compile = set->start_time;
		i++;
	}
}

static int	create_threads(t_set *set, t_coder *coders)
{
	int	i;

	i = 0;
	while (i < set->number_of_coders)
	{
		if (pthread_create(&coders[i].thread, NULL, routine, &coders[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	start_simulation(t_set *set, t_coder *coders)
{
	pthread_t	monitor_thread;
	int			i;

	set_last_compile(set, coders);
	if (create_threads(set, coders) != 0)
		return (1);
	if (pthread_create(&monitor_thread, NULL, monitor, coders) != 0)
		return (1);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < set->number_of_coders)
	{
		pthread_join(coders[i].thread, NULL);
		i++;
	}
	return (0);
}
