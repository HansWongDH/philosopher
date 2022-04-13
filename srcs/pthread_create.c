/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:24:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/13 16:18:46 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*eat(void *args)
{
	t_philo	*info;

	info = (t_philo *)args;
	// printf("Philo %d is thinking \n", info->id);
	if (info->id % 2 == 0)
		usleep(info->data->eat / 2);
	pthread_mutex_lock(&(info->data->lock[info->id]));
	pthread_mutex_lock(&(info->data->lock[(info->id + 1) % info->data->philo]));
	printf("Philo %d has taken a fork \n", info->id);
	printf("Philo %d is eating \n", info->id);
	usleep(info->data->eat);
	printf("Philo %d is sleeping \n", info->id);
	usleep(info->data->sleep);
	pthread_mutex_unlock(&(info->data->lock[(info->id + 1) % info->data->philo]));
	pthread_mutex_unlock(&(info->data->lock[info->id]));
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
