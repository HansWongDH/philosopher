/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:24:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/11 15:42:41 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	eat(t_philo *info)
{	
	pthread_mutex_lock(&(info->data->lock[info->rfork]));
	print_text("has taken a fork\n", YELLOW, info->id, info->data);
	pthread_mutex_lock(&(info->data->lock[info->lfork]));
	print_text("has taken a fork\n", YELLOW, info->id, info->data);
	print_text("is eating\n", GREEN, info->id, info->data);
	pthread_mutex_lock(&(info->data->checklock));
	info->last_eaten = get_ms();
	pthread_mutex_unlock(&(info->data->checklock));
	info->eaten--;
	ft_msleep(info->data->eat, get_ms());
	pthread_mutex_lock(&(info->data->checklock));
	if (!info->eaten)
		info->data->done++;
	pthread_mutex_unlock(&(info->data->checklock));
	pthread_mutex_unlock(&(info->data->lock[info->lfork]));
	pthread_mutex_unlock(&(info->data->lock[info->rfork]));
}

void	sleeping(t_philo *info)
{
	print_text("is sleeping\n", BLUE, info->id, info->data);
	ft_msleep(info->data->sleep, get_ms());
}

void	*action(void *args)
{
	t_philo			*info;

	info = (t_philo *)args;
	pthread_mutex_lock(&(info->data->startlock));
	info->last_eaten = get_ms();
	pthread_mutex_unlock(&(info->data->startlock));
	print_text("is thinking\n", CYAN, info->id, info->data);
	if (info->id % 2 == 0)
		ft_msleep(info->data->eat / 2, get_ms());
	while (info->eaten > 0 && !get_dead(info) && info->data->philo > 1)
	{
		eat(info);
		sleeping(info);
	}
	return (NULL);
}

void	create_thread(t_data *info)
{
	t_philo		*ph;
	pthread_t	checker;
	int			i;

	if (!ft_malloc((void *)&ph, sizeof(t_philo) * info->philo))
		return ;
	pthread_mutex_lock(&(info->startlock));
	i = 0;
	while (i < info->philo)
	{
		ph[i].id = i;
		ph[i].data = info;
		ph[i].rfork = i;
		ph[i].lfork = (i + 1) % info->philo;
		ph[i].last_eaten = get_ms();
		ph[i].eaten = info->timeleft;
		pthread_create(&(ph[i].thread), NULL, &action, (void *)&ph[i]);
		i++;
	}
	pthread_mutex_unlock(&(info->startlock));
	pthread_create(&checker, NULL, &death, ph);
	pthread_join(checker, NULL);
	join_thread(&ph, info->philo);
	free(ph);
}
