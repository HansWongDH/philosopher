/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:48:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/18 15:01:09 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

/*
	1. Since sem_t is a struct, __align is actually the value of it.
	2. sem_post will increase it by 1 while sem_wait will decreases it.
	3. Instead of using sem_wait, If else statement is used to check the value of
	the corresponding monitoring semaphore, if it is 1, the last_eaten time for the
	corresponding philo stored in the struct on main process will get updated
*/
void	kill_child(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->philo)
	{
		kill(info->pid[i], SIGTERM);
		i++;
	}
}

/*
	1. Instead of creating 1 thread per child process to check monitor 
	them locally,I opted to use main process with a single while loop 
	that loop thru their id to monitor them;
	2. Since sigaction/signal is forbidden, the program will 
	check with the value of semaphore manipulated by its child process;
	3. info->done will get increased by 1 everytime a philo is done
	with their eating, and the loop will stop once all of them have finished eating
*/
void	*death(void *arg)
{
	long long	cur;
	long long	diff;
	t_philo		*info;

	info = arg;
	while (return_stats(info))
	{
		cur = get_ms();
		pthread_mutex_lock(&(info->check));
		diff = cur - info->last_eaten;
		pthread_mutex_unlock(&(info->check));
		if (diff > info->data->death)
		{
			sem_wait(info->data->print);
			printf("%s%lld %d died\n", RED, get_ms(), info->id);
			exit(1);
			return (NULL);
		}
		usleep(info->data->philo);
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
