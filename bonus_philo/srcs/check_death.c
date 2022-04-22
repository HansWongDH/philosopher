/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:48:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/22 17:29:39 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	death_updating(t_data *info, int i)
{
		if (info->monitor[i]->__align == 1)
		{
			info->last_eaten[i] = get_ms();
			sem_wait(info->monitor[i]);
		}
}

void	kill_child(t_data *info)
{
	int	i;
	
	i = 0;
	while (i < info->philo)
	{
		kill(info->pid[i], SIGKILL);
		i++;
	}
}

void	*death(void *arg)
{
	long long	cur;
	long long	diff;
	t_data		*info;
	int			i;

	info = arg;
	i = 0;
	// printf("time is%lld\n", get_ms());
	while (info->done->__align != (long)info->philo && !info->dead)
	{
		death_updating(info, i);
		cur = get_ms();
		diff = cur - info->last_eaten[i];
		if (diff > info->death && !info->dead)
		{
			info->dead = 1;
			printf("%s%lld\tPhilosopher %d\tdied\n", RED, get_ms(), i);
			kill_child(info);
			return (NULL);
		}
		i++;
		if (i == info->philo)
			i = 0;
		usleep(info->death);
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
