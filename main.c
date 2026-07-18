/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 16:51:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/07/18 18:59:21 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	main(int argc, char **argv)
{
	if (argc != 2){
		printf("Unvalid option\n");
		return (0);
	}
	char **result;
	result = ft_split(argv[1], ' ');
	printf("%s", result[0]);
	printf("%s", result[1]);
	printf("%s", result[2]);
	return (0);
}
