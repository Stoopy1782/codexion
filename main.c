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
	if (argc != 9){
		printf("Unvalid option\n");
		return (0);
	}
	int number_of_coders;
	int time_to_burnout;
	int time_to_compile;
	int time_to_debug;
	int time_to_refactor;
	int number_of_compiles_required;
	int dongle_cooldown;
	char * scheduler;

	number_of_coders = atoi(argv[1]);
	time_to_burnout = atoi(argv[2]);
	time_to_compile = atoi(argv[3]);
	time_to_debug = atoi(argv[4]);
	time_to_refactor = atoi(argv[5]);
	number_of_compiles_required = atoi(argv[6]);
	dongle_cooldown = atoi(argv[7]);
	scheduler = argv[8];
	parse(number_of_coders, time_to_burnout, time_to_compile, time_to_debug, time_to_refactor,
	number_of_compiles_required, dongle_cooldown, scheduler);
	return (0);
}
