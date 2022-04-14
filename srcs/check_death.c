/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:48:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/14 18:55:37 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*death(void *arg)
{
	long long	cur;
	long long	diff;
	t_philo		*info;

	info = (t_philo *)arg;
	while (!info->data->done)
	{
		pthread_mutex_lock(&(info->data->deadlock));
		if (!info->data->done)
		{
			cur = get_milisec();
			diff = cur - info->last_eaten;
			// printf("done is %d \n diff is %lld", info->data->done, diff);
		}
		if (diff > (info->data->death) && !info->data->done)
		{
			info->data->done = 1;
			print_text("died\n", 4, info->id, info->data);
		}
		pthread_mutex_unlock(&(info->data->deadlock));
	}
	return (NULL);
}

