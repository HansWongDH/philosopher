/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:55:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/22 17:32:00 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	sem_kill(t_data *info)
{
	int		i;
	char	*str;
	char	*m;

	i = 0;
	while (i < info->philo)
	{
		str = ft_itoa(i);
		m = ft_strjoin(str, "d");
		sem_unlink(str);
		sem_unlink(m);
		sem_close(info->sem[i]);
		sem_close(info->monitor[i]);
		free(str);
		free(m);
		i++;
	}
	sem_unlink("start");
	sem_unlink("done");
	sem_close(info->start);
	sem_close(info->done);
	free(info->sem);
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
