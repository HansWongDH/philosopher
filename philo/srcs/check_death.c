/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:48:57 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/20 14:52:17 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*death(void *arg)
{
	long long	cur;
	long long	diff;
	t_philo		*info;
	int			i;

	info = arg;
	i = 0;
	while (info->data->done != info->data->philo && !info->data->dead)
	{
		cur = get_ms();
		diff = cur - info[i].last_eaten;
		if (diff > info->data->death && !info->data->dead)
		{
			info->data->dead = 1;
			printf("%s%lld\tPhilosopher %d\tdied\n", RED, get_ms(), info[i].id);
			return (NULL);
		}
		i++;
		if (i == info->data->philo)
			i = 0;
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
