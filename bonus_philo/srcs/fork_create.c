/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:25:15 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/22 17:34:02 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	eat(t_philo *info)
{	
	if (!info->data->dead)
	{
		sem_wait(info->data->sem[info->rfork]);
		print_text("has taken a fork\n", YELLOW, info->id, info->data);
		sem_wait(info->data->sem[info->lfork]);
		print_text("has taken a fork\n", YELLOW, info->id, info->data);
		print_text("is eating\n", GREEN, info->id, info->data);
		sem_post(info->data->monitor[info->id]);
		info->eaten--;
		ft_msleep(info->data->eat, get_ms());
		if (!info->eaten)
			sem_post(info->data->done);
		sem_post(info->data->sem[info->rfork]);
		sem_post(info->data->sem[info->lfork]);
	}
}

void	sleeping(t_philo *info)
{
	if (!info->data->dead)
	{
		print_text("is sleeping\n", BLUE, info->id, info->data);
		ft_msleep(info->data->sleep, get_ms());
	}
}

int	action(t_philo	*info)
{
	sem_wait(info->data->start);
	print_text("is thinking\n", CYAN, info->id, info->data);
	sem_post(info->data->start);
	if (info->id % 2 == 0 && !info->data->dead)
		ft_msleep(info->data->eat / 2, get_ms());
	while (info->eaten > 0 && !info->data->dead && info->data->philo > 1)
	{
		eat(info);
		sleeping(info);
	}
	exit(1);
}

int	fork_creation(t_data *info)
{
	t_philo		ph;
	int			i;

	i = 0;
	while (i < info->philo)
	{
		ph.id = i;
		ph.data = info;
		ph.rfork = i;
		ph.lfork = (i + 1) % info->philo;
		ph.eaten = info->timeleft;
		info->pid[i] = fork();
		info->last_eaten[i] = get_ms();
		if (info->pid[i] == 0)
			return (action(&ph));
		i++;
	}
	sem_post(info->start);
	return (0);
}