/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:40:54 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/17 20:26:52 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long	get_milisec(void)
{
	struct timeval	time;
	long long		milisec;
	long long		sec;

	gettimeofday(&time, NULL);
	sec = time.tv_sec;
	milisec = (sec * 1000) + (time.tv_usec / 1000);
	return (milisec);
}

void	self_sleep(int time)
{
	long long	cur;
	long long	start;

	start = get_milisec();
	cur = 0;
	while (cur < (long long)time)
	{
		cur = get_milisec() - start;
		usleep(1);
	}
}
