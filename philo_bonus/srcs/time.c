/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:40:54 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/22 22:11:49 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

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