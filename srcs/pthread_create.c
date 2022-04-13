/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:24:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/13 19:47:14 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*eat(void *args)
{
	t_philo	*info;

	info = (t_philo *)args;
	if (info->id % 2 == 0)
	{	
		print_text("is thinking \n", 0, info->id, info->data);
		usleep(info->data->eat / 2);
	}
	pthread_mutex_lock(&(info->data->lock[info->rfork]));
	pthread_mutex_lock(&(info->data->lock[info->lfork]));
	print_text("has taken a fork \n", 1, info->id, info->data);
	print_text("is eating \n", 2, info->id, info->data);
	usleep(info->data->eat);
	print_text("is sleeping \n", 3, info->id, info->data);
	usleep(info->data->sleep);
	pthread_mutex_unlock(&(info->data->lock[info->lfork]));
	pthread_mutex_unlock(&(info->data->lock[info->rfork]));
	return (NULL);
}

void	create_thread(t_data *info)
{
	t_philo	ph[250];
	int		i;

	i = 0;
	while (i < info->philo)
	{
		ph[i].id = i;
		ph[i].data = info;
		ph[i].rfork = i;
		ph[i].lfork = (i + 1) % info->philo;
		pthread_create(&(ph[i].thread), NULL, &eat, (void *)&ph[i]);
		i++;
	}
	i = 0;
	while (i < info->philo)
	{
		pthread_join(ph[i++].thread, NULL);
		usleep (50);
	}
}
