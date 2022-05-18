/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:55:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/18 14:49:03 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

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
