/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_lock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:09:07 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/08 22:29:05 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	destroy_mutex(t_data *info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(info->print));
	while (i < info->philo)
		pthread_mutex_destroy(&(info->lock[i++]));
	pthread_mutex_destroy(&(info->checklock));
	pthread_mutex_destroy(&(info->startlock));
	free(info->lock);
}
