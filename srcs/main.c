/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:50:04 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/12 18:41:46 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	grab_left(t_philo *info)
{
	int	i;
	int	j;

	if (info->id == info->data->philo - 1)
		i = 0;
	else
		i = info->id + 1;
	j = pthread_mutex_lock(&(info->data->lock[i]));
	// printf("%d left\n", i);
	return (j);
}

int	grab_right(t_philo *info)
{
	int	i;
	int	j;

	if (info->id == 0)
		i = info->data->philo - 1;
	else
		i = info->id - 1;
	j = pthread_mutex_lock(&(info->data->lock[i]));
	// printf("%d right\n", i);
	return (j);
}

int	drop_left(t_philo *info)
{
	int	i;
	int	j;

	if (info->id == info->data->philo - 1)
		i = 0;
	else
		i = info->id + 1;
	j = pthread_mutex_unlock(&(info->data->lock[i]));
	// printf("%d left\n", j);
	return (j);
}

int	drop_right(t_philo *info)
{
	int	i;
	int	j;

	if (info->id == 0)
		i = info->data->philo - 1;
	else
		i = info->id - 1;
	j = pthread_mutex_unlock(&(info->data->lock[i]));
	// printf("%d right\n", j);
	return (j);
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
	if (!stats->id % 1)
		usleep(500);
	grab_left(stats);
	grab_right(stats);
	printf("Philosopher %d is eating \n", stats->id);
	usleep(stats->data->eat);
	drop_left(stats);
	drop_right(stats);
	printf("Philosopher %d is sleeping \n", stats->id);
	usleep(stats->data->sleep);

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
