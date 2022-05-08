/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:26:36 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/08 15:50:11 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	error(int i)
{
	if (i == 0)
		ft_putstr_fd("Error: Invalid number of argument\n", 2);
	if (i == 1)
		ft_putstr_fd("Error: Invalid number\n", 2);
	if (i == 2)
		ft_putstr_fd("Error: Input is not a number\n", 2);
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
		if (!ft_checkdigit(av[i]))
			return (error(2));
		if (ft_atoi(av[i]) <= 0)
			return (error(1));
		i++;
	}
	return (1);
}

void	build_info(t_data *info, char **argv, int argc)
{
	info->philo = ft_atoi(argv[1]);
	info->death = ft_atoi(argv[2]);
	info->eat = ft_atoi(argv[3]);
	info->sleep = ft_atoi(argv[4]);
	info->dead = 0;
	info->done = 0;
	info->start = 0;
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) > 0)
			info->timeleft = ft_atoi(argv[5]);
		else
			info->timeleft = 1;
	}
	else
		info->timeleft = INT_MAX;
	pthread_mutex_init(&(info->print), NULL);
	pthread_mutex_init(&(info->checklock), NULL);
	pthread_mutex_init(&(info->startlock), NULL);
}
