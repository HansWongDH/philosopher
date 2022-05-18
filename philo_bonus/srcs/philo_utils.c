/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:34:35 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/18 15:08:41 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

/*
	Print function with semaphore
*/
void	print_text(char *s, char *c, int id, t_data *info)
{
	sem_wait(info->print);
	printf("%s%lld %d %s", c, get_ms(), id, s);
	sem_post(info->print);
}

int	return_stats(t_philo *info)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(info->check));
	if (!info->fin)
		i = 1;
	pthread_mutex_unlock(&(info->check));
	return (i);
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

/*
	1. customized sleep function for accurate sleep timing;
	2. usleep(200) is to adjust according to pc performance and
	200 is the sweet spot for me on campus 's iMAC
*/
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
