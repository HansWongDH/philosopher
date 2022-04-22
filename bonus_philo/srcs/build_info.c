/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:26:36 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/22 21:10:35 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (0);
}

int	ft_checkdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (!ft_isdigit(str[i]) && str[i])
		return (0);
	return (1);
}

int	input_checking(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (error());
		if (!ft_checkdigit(av[i]))
			return (error());
		i++;
	}
	return (1);
}

void	sem_generate(t_data *info)
{
	int		i;
	char	*str;
	char	*d;

	i = 0;
	info->sem = malloc(sizeof(sem_t *) * info->philo);
	info->monitor = malloc(sizeof(sem_t *) * info->philo);
	while (i < info->philo)
	{
		str = ft_itoa(i);
		d = ft_strjoin(str, "d");
		info->sem[i] = ft_sem_create(str, 1);
		info->monitor[i] = ft_sem_create(d, 0);
		free(str);
		free(d);
		i++;
	}
}

void	build_info(t_data *info, char **argv, int argc)
{
	info->philo = ft_atoi(argv[1]);
	info->death = ft_atoi(argv[2]);
	info->eat = ft_atoi(argv[3]);
	info->sleep = ft_atoi(argv[4]);
	info->dead = 0;
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) > 0)
			info->timeleft = ft_atoi(argv[5]);
		else
			info->timeleft = 1;
	}
	else
		info->timeleft = 9999999;
	info->start = sem_open("start", O_CREAT, 0664, 0);
	info->done = sem_open("done", O_CREAT, 0664, 0);
	info->print = sem_open("print", O_CREAT, 0664, 1);
	info->pid = malloc(sizeof(pid_t) * info->philo);
	info->last_eaten = malloc(sizeof(long long) * info->philo);
	sem_generate(info);
}
