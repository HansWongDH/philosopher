/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:51:19 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/22 17:40:40 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	main(int argc, char **argv)
{
	t_data		info;
	pthread_t	monitor;

	if (argc != 5 && argc != 6)
		return (0);
	if (!input_checking(argv, argc))
		exit(1);
	build_info(&info, argv, argc);
	fork_creation(&info);
	if (getpid() > 0)
	{
		pthread_create(&monitor, NULL, &death, &info);
		pthread_join(monitor, NULL);
		wait_for_my_child(info);
	}
	sem_kill(&info);
	exit(1);
}
