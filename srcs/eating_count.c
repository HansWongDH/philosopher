/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:00:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/17 19:22:57 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	self_sleep(int time, pthread_mutex_t *lock)
{
	long long	cur;
	long long	start;
	
	(void)lock;
	// pthread_mutex_lock(lock);
	start = get_milisec();
	cur = 0;
	while (cur < (long long)time)
	{
		cur = get_milisec() - start;
		usleep(1);
	}
	// pthread_mutex_unlock(lock);
}