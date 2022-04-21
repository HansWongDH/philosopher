/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:48:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/21 19:23:29 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*death(void *arg)
{
	long long	cur;
	long long	diff;
	t_philo		*info;

	info = arg;
	while (info->data->done != info->data->philo && !info->data->dead)
	{
		cur = get_ms();
		diff = cur - info->last_eaten;
		if (diff > info->data->death && !info->data->dead)
		{
			info->data->dead = 1;
			printf("%s%lld\tPhilosopher %d\tdied\n", RED, get_ms(), info->id);
			return (NULL);
		}
		usleep(info->data->death);
	}
	return (NULL);
}

int	ft_malloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!(*ptr))
		return (0);
	return (1);
}
