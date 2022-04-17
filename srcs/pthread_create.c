/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:24:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/17 19:18:36 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	eat(t_philo *info, pthread_mutex_t *lock)
{	
	if (info->data->dead == 0)
	{
		pthread_mutex_lock(&(info->data->lock[info->rfork]));
		print_text("has taken a fork\n", YELLOW, info->id, info->data);
		printf("fork is is %d\n", info->rfork);
		pthread_mutex_lock(&(info->data->lock[info->lfork]));
		print_text("has taken a fork\n", YELLOW, info->id, info->data);
		printf("fork is is %d\n", info->lfork);
		print_text("is eating\n", GREEN, info->id, info->data);
		info->last_eaten = get_milisec();
		info->eaten--;
		self_sleep(info->data->eat, lock);
		pthread_mutex_lock(&(info->data->checklock));
		if (!info->eaten)
			info->data->done++;
		pthread_mutex_unlock(&(info->data->checklock));
		pthread_mutex_unlock(&(info->data->lock[info->lfork]));
		pthread_mutex_unlock(&(info->data->lock[info->rfork]));
	}
}

void	sleeping(t_philo *info, pthread_mutex_t *lock)
{
	if (info->data->dead == 0)
	{
		print_text("is sleeping\n", BLUE, info->id, info->data);
		self_sleep(info->data->sleep, lock);
	}
}

void	*action(void *args)
{
	t_philo			*info;
	pthread_mutex_t	sleep;
	
	info = (t_philo *)args;
	pthread_mutex_init(&sleep, NULL);
	if (info->id % 2 == 0 && info->data->dead == 0)
	{	
		print_text("is thinking\n", CYAN, info->id, info->data);
		self_sleep(info->data->eat / 2, &sleep);
	}
	while (info->eaten > 0)
	{
		eat(info, &sleep);
		sleeping(info, &sleep);	
	}
	pthread_mutex_destroy(&sleep);
	return (NULL);
}

void	create_thread(t_data *info)
{
	t_philo		*ph;
	pthread_t	*checker;
	int		i;
	
	ph = malloc(sizeof (t_philo) * info->philo);
	checker = malloc(sizeof (pthread_t) * info->philo);
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
	i = 0;
	while (i < info->philo)
	{
		pthread_join(ph[i].thread, NULL);
		pthread_join(checker[i], NULL);
		i++;
	}
	free(ph);
	free(checker);
}
