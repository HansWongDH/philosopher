/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:50:04 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/12 19:30:34 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	grab_fork(t_philo *info)
{
	pthread_mutex_lock(&(info->data->lock[info->id + (1 % info->data->philo)]));
	printf("philo %d is eating \n", info->id);
	usleep(info->data->eat);
	pthread_mutex_unlock(&(info->data->lock[info->id]));
	pthread_mutex_unlock(&(info->data->lock[info->id + (1 % info->data->philo)]));
}

void	drop_fork(t_philo *info)
{
	pthread_mutex_unlock(&(info->data->lock[info->id]));
}

void	build_info(t_data *info, char **argv)
{
	info->philo = ft_atoi(argv[1]);
	info->death = ft_atoi(argv[2]) * 1000;
	info->eat = ft_atoi(argv[3]) * 1000;
	info->sleep = ft_atoi(argv[4]) * 1000;
	info->dead = 0;
}

void	*eat(void *args)
{
	t_philo	*stats;

	stats = (t_philo *)args;
	while (1)
	{
		if (!pthread_mutex_lock(&(stats->data->lock[stats->id])))
			grab_fork(stats);
		printf("Philo %d is sleeping \n", stats->id);
		usleep(stats->data->sleep);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		info;
	t_philo		*ph;
	int			i;

	if (argc != 5)
		return (0);
	if (argc == 5)
		build_info(&info, argv);
	i = 0;
	info.lock = malloc(sizeof(pthread_mutex_t *) * info.philo);
	while (i < info.philo)
		pthread_mutex_init(&(info.lock[i++]), NULL);
	ph = malloc(sizeof(t_philo *) * info.philo);
	i = 0;
	while (i < info.philo)
	{
		ph[i].id = i;
		ph[i].data = &info;
		pthread_create(&(ph[i].thread), NULL, &eat, (void *)&ph[i]);
		i++;
	}
	i = 0;
	while (i < info.philo)
	{
		pthread_join(ph[i++].thread, NULL);
		usleep (500);
	}
}
