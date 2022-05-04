/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:26:36 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/04 04:35:48 by wding-ha         ###   ########.fr       */
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

/*
	1. Error handling function that filtered out
	non-digit, negative number, weird cases like 12-
	2. my ft_atoi behave like real atoi, return 0 or -1
	on number that exceed INT_MIN and INT_MAX which will get
	filtered out as well;
*/
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

/*
	1. Generate 2 set of array of semaphore, 1 represent fork,
	the other one use to communicate with death_checker 
*/
void	sem_generate(t_data *info)
{
	int		i;
	char	*str;
	char	*d;
	char	*s;

	i = 0;
	if (!ft_malloc((void *)&(info->sem), sizeof(sem_t *) * info->philo))
		return (freestruct(info));
	if (!ft_malloc((void *)&(info->monitor), sizeof(sem_t *) * info->philo))
		return (freestruct(info));
	while (i < info->philo)
	{
		str = ft_itoa(i);
		d = ft_strjoin(str, "d");
		s = ft_strjoin(str,  "s");
		info->sem[i] = ft_sem_create(str, 1);
		info->monitor[i] = ft_sem_create(d, 0);
		info->done[i] = ft_sem_create(s, 0);
		free(str);
		free(d);
		free(s);
		i++;
	}
	info->deathcheck = sem_open("deathcheck", O_CREAT, 0664, 1);
}

/*
	1. Initialize struct, transform input into struct for philo generation;
	2. Creation of multiple semaphore that shared among process;
	3. start - synchronize the starting of process
	4. done - keep track on how many philo have done with their eating
	5. print - semaphore for printing messages so it won't jumble up
*/
void	build_info(t_data *info, char **argv, int argc)
{
	
	info->philo = ft_atoi(argv[1]);
	sem_unchain(info);
	info->death = ft_atoi(argv[2]);
	info->eat = ft_atoi(argv[3]);
	info->sleep = ft_atoi(argv[4]);
	info->dead = 0;
	info->fin = 0;
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) > 0)
			info->timeleft = ft_atoi(argv[5]);
		else
			info->timeleft = 1;
	}
	else
		info->timeleft = INT_MAX;
	info->start = sem_open("start", O_CREAT, 0664, 0);
	info->print = sem_open("print", O_CREAT, 0664, 1);
	info->check = sem_open("check", O_CREAT, 0664, 0);
	if (!ft_malloc((void *)&(info->pid), sizeof(pid_t) * info->philo))
		return (freestruct(info));
	if (!ft_malloc((void *)&(info->last_eaten), 8 * info->philo))
		return (freestruct(info));
	sem_generate(info);
}
