/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:26:36 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/18 13:25:49 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int		error(void)
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

int		input_checking(char **av, int ac)
{
	int	i;
	
	i = 1;
	// if (ft_atoi(av[1]) <= 0)
	// 	return (error());
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
		info->timeleft = 9999999;
	pthread_mutex_init(&(info->print), NULL);
	pthread_mutex_init(&(info->checklock), NULL);
}
