/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:55:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/22 23:16:32 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	freestruct(t_data *info)
{
	if (info->pid)
		free(info->pid);
	if (info->last_eaten)
		free(info->last_eaten);
}

void	sem_unchain(t_data *info)
{
	char	*str;
	char	*m;
	int		i;

	i = 0;
	while (i < info->philo)
	{
		str = ft_itoa(i);
		m = ft_strjoin(str, "d");
		sem_unlink(str);
		sem_unlink(m);
		free(str);
		free(m);
		i++;
	}
	sem_unlink("start");
	sem_unlink("done");
	sem_unlink("print");
}

void	sem_kill(t_data *info)
{
	int		i;

	i = 0;
	sem_unchain(info);
	while (i < info->philo)
	{
		sem_close(info->sem[i]);
		sem_close(info->monitor[i]);
		i++;
	}
	sem_close(info->start);
	sem_close(info->done);
	sem_close(info->print);
	free(info->sem);
	free(info->monitor);
}

sem_t	*ft_sem_create(char *s, int i)
{
	sem_t	*sem;

	sem = sem_open(s, O_CREAT, 0664, i);
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
