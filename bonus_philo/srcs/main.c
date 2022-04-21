/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:51:19 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/21 17:59:10 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	main(int argc, char **argv)
{
	t_data		info;

	if (argc != 5 && argc != 6)
		return (0);
	if (!input_checking(argv, argc))
		exit(1);
	build_info(&info, argv, argc);
	fork_creation(&info);
	if (getpid() > 0)
		wait_for_my_child(info);
	sem_kill(&info);
	exit(1);
}