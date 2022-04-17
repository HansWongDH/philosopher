/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:26:36 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/17 20:13:24 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	build_info(t_data *info, char **argv, int argc)
{
	info->philo = ft_atoi(argv[1]);
	info->death = ft_atoi(argv[2]);
	info->eat = ft_atoi(argv[3]);
	info->sleep = ft_atoi(argv[4]);
	info->dead = 0;
	info->done = 0;
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) > 0)
			info->timeleft = ft_atoi(argv[5]);
		else
			info->timeleft = 1;
	}
	else
		info->timeleft = 9999999;
	pthread_mutex_init(&(info->print), NULL);
	pthread_mutex_init(&(info->checklock), NULL);
}