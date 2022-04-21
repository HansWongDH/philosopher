/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:51:19 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/21 16:35:30 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	sem_kill(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->philo)
	{
		sem_unlink(ft_itoa(i));
		sem_close(info->sem[i]);
		i++;
	}
	sem_unlink("start");
	sem_close(info->start);
}

void	wait_for_my_child(t_data info)
{
	int	stats;
	int	i;

	i = 0;
	while (i < info.philo)
	{
		waitpid(info.pid[i], &stats, 0);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		info;
	int			i;

	if (argc != 5 && argc != 6)
		return (0);
	if (!input_checking(argv, argc))
		exit(1);
	build_info(&info, argv, argc);
	i = 0;
	info.sem = malloc(sizeof(sem_t *) * info.philo);
	while (i < info.philo)
	{
		info.sem[i] = ft_sem_create(i);
		i++;
	}
	fork_creation(&info);
	if (getpid() > 0)
		wait_for_my_child(info);
	sem_kill(&info);
	exit(1);
}