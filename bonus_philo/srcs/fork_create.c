/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:25:15 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/22 22:51:58 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

/*
	1.sem_post monitor semaphore is to trigger 
	the refresh of last_eaten time on main process
*/
void	eat(t_philo *info)
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
	sem_post(info->data->sem[info->lfork]);
	sem_post(info->data->sem[info->rfork]);
}

void	sleeping(t_philo *info)
{
	print_text("is sleeping\n", BLUE, info->id, info->data);
	ft_msleep(info->data->sleep, get_ms());
}

/*
	1. sem_t start started as 0, hence all process 
	will be waiting until the switch is flipped
	2. after that, it will flip its corresponding 
	monitor sem_t to refresh the last_eaten time;
	3. even number id will get delayed for half of eating time
*/
int	action(t_philo	*info)
{
	sem_wait(info->data->start);
	sem_post(info->data->monitor[info->id]);
	print_text("is thinking\n", CYAN, info->id, info->data);
	sem_post(info->data->start);
	if (info->id % 2 == 0)
		usleep(info->data->eat * 500);
	while (info->eaten > 0 && info->data->philo > 1)
	{
		eat(info);
		sleeping(info);
	}
	exit(1);
}

void	get_eaten_time(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->philo)
	{
		info->last_eaten[i] = get_ms();
		i++;
	}
}

/*
	1. the creation of philo as a child process;
	2. Since they duplicate the value, instead of array of struct like mandatory,
	I used 1 struct and update its value before the forking process;
	3. I also store pid of child process 
	into an array in the main struct t_data;
	4. Last_eaten time will get initialized once the 
	creation of child process is finished
	5. In order to synchronize their starting time, 
	they will lie dormant until sem_t start turn into 1
	which happen after the creation of last child process;
*/
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
		if (info->pid[i] == 0)
			return (action(&ph));
		i++;
	}
	get_eaten_time(info);
	sem_post(info->start);
	return (0);
}
