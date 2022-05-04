/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:55:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/04 04:35:42 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	freestruct(t_data *info)
{
	if (info->pid)
		free(info->pid);
	if (info->last_eaten)
		free(info->last_eaten);
	if (info->sem)
		free(info->sem);
	if (info->monitor)
		free(info->monitor);	
}

void	sem_unchain(t_data *info)
{
	char	*str;
	char	*d;
	char	*s;
	int		i;

	i = 0;
	while (i < info->philo)
	{
		str = ft_itoa(i);
		d = ft_strjoin(str, "d");
		s = ft_strjoin(str, "s");
		sem_unlink(str);
		sem_unlink(d);
		sem_unlink(s);
		free(str);
		free(d);
		free(s);
		i++;
	}
	sem_unlink("start");
	sem_unlink("done");
	sem_unlink("print");
	sem_unlink("check");
	sem_unlink("deathcheck");
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
		sem_close(info->done[i]);
		i++;
	}
	sem_close(info->start);
	sem_close(info->print);
	sem_close(info->check);
	sem_close(info->deathcheck);
}

sem_t	*ft_sem_create(char *s, int i)
{
	sem_t	*sem;

	sem = sem_open(s, O_CREAT, 0664, i);
	return (sem);
}
