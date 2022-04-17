/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:48:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/17 20:35:59 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*death(void *arg)
{
	long long	cur;
	long long	diff;
	t_philo		*info;

	info = (t_philo *)arg;
	while (info->data->done != info->data->philo && info->data->dead == 0)
	{
		cur = get_milisec();
		diff = cur - info->last_eaten;
		if (diff > (info->data->death) && !info->data->dead)
		{
			info->data->dead = 1;
			printf("%s%lld Philosopher %d died\n", RED, get_milisec(), info->id);
			exit(1);
		}
	}
	return (NULL);
}
