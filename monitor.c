/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 17:21:26 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/02 20:12:01 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	check_burnout(t_coder *coders, t_set *set)
{
	int	i;

	i = 0;
	while (i < set->number_of_coders)
	{
		if (get_time() - coders[i].last_compile > set->time_to_burnout)
		{
			set->is_stopped = 1;
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

	i = 0;
	while (i < set->number_of_coders)
	{
		if (coders[i].compile_count < set->number_of_compiles_required)
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
	while (set->is_stopped != 1)
	{
		if (check_burnout(coders, set))
			return (NULL);
		if (check_finnished(coders, set))
		{
			set->is_stopped = 1;
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
