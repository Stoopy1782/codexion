/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:38:48 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/10 16:43:22 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_all(t_set *set, t_coder *coders)
{
	int	i;

	i = 0;
	while (i < set->number_of_coders)
	{
		pthread_mutex_destroy(&coders->dongles[i].lock_d);
		pthread_mutex_destroy(&coders->dongles[i].lock_sch);
		pthread_cond_destroy(&coders->dongles[i].lock_start);
		pthread_mutex_destroy(&coders[i].lock_c);
		i++;
	}
	pthread_mutex_destroy(&set->lock_s);
	pthread_mutex_destroy(&set->lock_stop);
	if (coders->dongles)
		free(coders->dongles);
	if (coders)
		free(coders);
}
