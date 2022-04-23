/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:48:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/22 23:15:49 by wding-ha         ###   ########.fr       */
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
void	death_updating(t_data *info, int i)
{
	if (info->monitor[i]->__align >= 1)
	{
		info->last_eaten[i] = get_ms();
		info->monitor[i]->__align = 0;
	}
}

void	kill_child(t_data *info)
{
	int	i;

	i = 0;
	info->dead = 1;
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
	t_data		*info;
	int			i;

	info = arg;
	i = 0;
	while (info->done->__align != (long)info->philo && !info->dead)
	{
		death_updating(info, i);
		cur = get_ms();
		diff = cur - info->last_eaten[i];
		if (diff > info->death && !info->dead)
		{
			kill_child(info);
			printf("%s%lld\tPhilosopher %d\tdied\n", RED, get_ms(), i);
			return (NULL);
		}
		i++;
		if (i == info->philo)
			i = 0;
		usleep(info->philo);
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
