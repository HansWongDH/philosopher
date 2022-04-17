/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:24:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/17 22:57:23 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	eat(t_philo *info)
{	
	if (info->data->dead == 0)
	{
		pthread_mutex_lock(&(info->data->lock[info->rfork]));
		print_text("has taken a fork\n", YELLOW, info->id, info->data);
		pthread_mutex_lock(&(info->data->lock[info->lfork]));
		print_text("has taken a fork\n", YELLOW, info->id, info->data);
		print_text("is eating\n", GREEN, info->id, info->data);
		info->last_eaten = get_milisec();
		info->eaten--;
		self_sleep(info->data->eat);
		pthread_mutex_lock(&(info->data->checklock));
		if (!info->eaten)
			info->data->done++;
		pthread_mutex_unlock(&(info->data->checklock));
		pthread_mutex_unlock(&(info->data->lock[info->lfork]));
		pthread_mutex_unlock(&(info->data->lock[info->rfork]));
	}
}

void	sleeping(t_philo *info)
{
	if (info->data->dead == 0)
	{
		print_text("is sleeping\n", BLUE, info->id, info->data);
		self_sleep(info->data->sleep);
	}
}

void	*action(void *args)
{
	t_philo			*info;
	pthread_mutex_t	sleep;

	info = (t_philo *)args;
	pthread_mutex_init(&sleep, NULL);
	print_text("is thinking\n", CYAN, info->id, info->data);
	if (info->id % 2 == 0 && info->data->dead == 0)
		self_sleep(info->data->eat / 2);
	while (info->eaten > 0 && info->data->dead == 0)
	{
		eat(info);
		sleeping(info);
	}
	pthread_mutex_destroy(&sleep);
	return (NULL);
}

void	join_thread(t_philo **ph, pthread_t **checker, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join((*ph)[i].thread, NULL);
		pthread_join((*checker)[i], NULL);
		i++;
	}
}

void	create_thread(t_data *info)
{
	t_philo		*ph;
	pthread_t	*checker;
	int			i;

	if (!ft_malloc((void *)&ph, sizeof(t_philo) * info->philo))
		return ;
	if (!ft_malloc((void *)&checker, sizeof(pthread_t) * info->philo))
		return ;
	i = 0;
	while (i < info->philo)
	{
		ph[i].id = i;
		ph[i].data = info;
		ph[i].rfork = i;
		ph[i].lfork = (i + 1) % info->philo;
		ph[i].last_eaten = get_milisec();
		ph[i].eaten = info->timeleft;
		pthread_create(&(ph[i].thread), NULL, &action, (void *)&ph[i]);
		pthread_create(&(checker[i]), NULL, &death, (void *)&ph[i]);
		i++;
	}
	join_thread(&ph, &checker, info->philo);
	free(ph);
	free(checker);
}
