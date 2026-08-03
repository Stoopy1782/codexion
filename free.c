/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:38:48 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/03 18:52:07 by ykojima          ###   ########.fr       */
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
		i++;
	}
	if (coders->dongles)
		free(coders->dongles);
	if (coders)
		free(coders);
}
