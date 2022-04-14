/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:00:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/14 16:44:56 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*eat_count(void	*args)
{
	t_data	*info;

	info = args;
	pthread_mutex_lock(&(info->countlock));
	while (info->timeleft > 0)
	{
		create_thread(info);
		info->timeleft--;
	}
	if (info->timeleft == 0)
		info->dead = 2;
	pthread_mutex_unlock(&(info->countlock));
	return (NULL);
}

void	eating_count(t_data *info)
{
	pthread_t	count;
	
	pthread_mutex_init(&(info->countlock), NULL);
	pthread_create(&count, NULL, &eat_count, (void *)info);
	pthread_join(count, NULL);
	pthread_detach(count);
	pthread_mutex_destroy(&(info->countlock));
}