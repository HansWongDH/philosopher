/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:24:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/14 18:48:55 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	action(t_philo *info)
{
	if (info->data->dead == 0)
		print_text("has taken a fork\n", 1, info->id, info->data);
	if (info->data->dead == 0)
	{
		print_text("is eating\n", 2, info->id, info->data);
		info->last_eaten = get_milisec();
		usleep(info->data->eat);
	}
}
void	*eat(void *args)
{
	t_philo	*info;

	info = (t_philo *)args;
	
	if (info->data->dead == 0)
	{
		if (info->id % 2 == 0 && info->data->dead == 0)
		{	
			print_text("is thinking\n", 0, info->id, info->data);
			usleep(info->data->eat / 2);
		}
		pthread_mutex_lock(&(info->data->lock[info->rfork]));
		pthread_mutex_lock(&(info->data->lock[info->lfork]));
		action(info);
		pthread_mutex_unlock(&(info->data->lock[info->lfork]));
		pthread_mutex_unlock(&(info->data->lock[info->rfork]));
		if (info->data->dead == 0)
		{
			print_text("is sleeping\n", 3, info->id, info->data);
			usleep(info->data->sleep);
		}
	}
	return (NULL);
}

void	create_thread(t_data *info)
{
	t_philo		*ph;
	pthread_t	*checker;
	int		i;
	
	ph = malloc(sizeof (t_philo) * info->philo);
	checker = malloc(sizeof (pthread_t *) * info->philo);
	i = 0;
	while (i < info->philo)
	{
		ph[i].id = i;
		ph[i].data = info;
		ph[i].rfork = i;
		ph[i].lfork = (i + 1) % info->philo;
		ph[i].last_eaten = get_milisec();
		ph[i].die = 0;
		pthread_create(&(ph[i].thread), NULL, &eat, (void *)&ph[i]);
		pthread_create(&(checker[i]), NULL, &death, (void *)&ph[i]);
		i++;
	}
	i = 0;
	while (i < info->philo)
	{
		pthread_join(ph[i].thread, NULL);
		pthread_join(checker[i], NULL);
		i++;
	}
	pthread_mutex_lock(&(info->checklock));
	if (info->timeleft == 0 || info->done == 1)
			info->done = 1;
	pthread_mutex_unlock(&(info->checklock));
	free(ph);
	free(checker);
}
