/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:55:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/07/07 17:42:12 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

// void	sem_remove(t_data *info)
// {
// 	int		i;
// 	char	*s;

// 	i = 0;
// 	while (i < info->philo)
// 	{
// 		s = ft_itoa(i);
// 		sem_unlink(s);
// 		sem_close(info->done[i]);
// 		free(s);
// 		i++;
// 	}
// }

void	freestruct(t_data *info)
{
	if (info->pid)
		free(info->pid);
}

void	sem_unchain(void)
{
	sem_unlink("start");
	sem_unlink("print");
	sem_unlink("/fork");
}

void	sem_kill(t_data *info)
{
	sem_unchain();
	sem_close(info->start);
	sem_close(info->print);
	sem_close(info->sem);
}
