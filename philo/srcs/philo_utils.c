/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:34:35 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/11 15:41:22 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	print_text(char *s, char *c, int id, t_data *info)
{
	pthread_mutex_lock(&(info->print));
	if (info->dead == 0)
		printf("%s%lld %d %s", c, get_ms(), id, s);
	pthread_mutex_unlock(&(info->print));
}

long long	get_ms(void)
{
	struct timeval	time;
	long long		milisec;
	long long		sec;

	gettimeofday(&time, NULL);
	sec = time.tv_sec;
	milisec = (sec * 1000) + (time.tv_usec / 1000);
	return (milisec);
}

void	ft_msleep(int time, long long start)
{
	long long	cur;

	cur = 0;
	while (cur < (long long)time)
	{
		cur = get_ms() - start;
		usleep(200);
	}
}

void	join_thread(t_philo **ph, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join((*ph)[i].thread, NULL);
		i++;
	}
}

int	ft_malloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!(*ptr))
		return (0);
	return (1);
}
