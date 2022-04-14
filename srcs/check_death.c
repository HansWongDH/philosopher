/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:48:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/14 16:47:45 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*death(void *arg)
{
	long long	cur;
	long long	diff;
	t_philo		*info;

	info = (t_philo *)arg;
	while (info->data->timeleft != 0 && info->data->dead == 0)
	{
		pthread_mutex_lock(&(info->data->deadlock));
		cur = get_milisec();
		diff = cur - info->last_eaten;
		// printf("diff is %lld \n", diff);
		if (diff > (info->data->death) && info->data->dead == 0)
		{
			info->data->dead = 1;
			print_text("died\n", 4, info->id, info->data);
			pthread_detach(info->thread);
		}
		pthread_mutex_unlock(&(info->data->deadlock));
	}
	return (NULL);
}

