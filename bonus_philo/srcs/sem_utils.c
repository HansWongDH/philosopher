/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:55:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/21 18:20:15 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	sem_kill(t_data *info)
{
	int		i;
	char	*str;

	i = 0;
	while (i < info->philo)
	{
		str = ft_itoa(i);
		sem_unlink(str);
		sem_close(info->sem[i]);
		free(str);
		i++;
	}
	sem_unlink("start");
	sem_close(info->start);
	free(info->sem);
}

sem_t	*ft_sem_create(int i)
{
	char	*str;
	sem_t	*sem;

	str = ft_itoa(i);
	sem = sem_open(str, O_CREAT, 0664, 1);
	free(str);
	return (sem);
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
