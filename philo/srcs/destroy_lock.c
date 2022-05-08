/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_lock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:09:07 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/08 15:55:08 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	destroy_mutex(t_data *info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(info->print));
	while (i < info->philo)
		pthread_mutex_destroy(&(info->lock[i++]));
	pthread_mutex_destroy(&(info->checklock));
	pthread_mutex_destroy(&(info->startlock));
	free(info->lock);
}

int		get_start(t_philo *info)
{
	static int	i;
	
	i = 0;
	pthread_mutex_lock(&(info->data->startlock));
	if (info->data->start == 1)
		i = 1;
	pthread_mutex_unlock(&(info->data->startlock));
	return (i);
}