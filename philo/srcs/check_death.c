/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:48:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/08 22:31:21 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	get_status(t_philo *info)
{
	static int	i;

	pthread_mutex_lock(&(info->data->checklock));
	i = info->data->done;
	pthread_mutex_unlock(&(info->data->checklock));
	return (i);
}

void	*death(void *arg)
{
	long long	cur;
	long long	diff;
	t_philo		*info;
	int			i;

	info = arg;
	i = 0;
	while (get_status(info) != info->data->philo && !info->data->dead)
	{
		cur = get_ms();
		pthread_mutex_lock(&(info->data->checklock));
		diff = cur - info[i].last_eaten;
		if (diff > info->data->death && !info->data->dead)
		{
			info->data->dead = 1;
			printf("%s%lld\tPhilosopher %d\tdied\n", RED, get_ms(), info[i].id);
			pthread_mutex_unlock(&(info->data->checklock));
			return (NULL);
		}
		pthread_mutex_unlock(&(info->data->checklock));
		i++;
		if (i == info->data->philo)
			i = 0;
		usleep(info->data->death);
	}
	return (NULL);
}

int	ft_malloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!(*ptr))
		return (0);
	return (1);
}
