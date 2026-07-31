/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:49:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/07/31 19:30:37 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_dongle	*create_dondles(t_set *set)
{
	t_dongle	*dongles;
	int			i;

	dongles = malloc(sizeof(t_dongle) * set->number_of_coders);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < set->number_of_coders)
	{
		dongles[i].id = i + 1;
		dongles[i].available_time = 0;
		dongles[i].set = set;
		// ⭕️ Mutex を必ず初期化する
		if (pthread_mutex_init(&dongles[i].lock_d, NULL) != 0)
			return (NULL);
		i++;
	}
	return (dongles);
}

t_coder	*create_coders(t_set *set, t_dongle *dongles)
{
	t_coder	*coders;
	int		i;

	coders = malloc(sizeof(t_coder) * set->number_of_coders);
	if (!coders)
		return (NULL);
	i = 0;
	while (i < set->number_of_coders)
	{
		coders[i].id = i + 1;
		coders[i].compile_count = 0;
		coders[i].is_burnout = 0;
		coders[i].last_compile = 0;
		coders[i].set = set;
		coders[i].dongles = dongles;
		i++;
	}
	return (coders);
}
