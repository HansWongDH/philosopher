/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:34:35 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/04 04:42:07 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

/*
	Print function with semaphore
*/
void	print_text(char *s, char *c, int id, t_data *info)
{
	sem_wait(info->print);
		printf("%s%lld\tPhilosopher %d\t%s", c, get_ms(), id, s);
	sem_post(info->print);
}

void	*done(void *data)
{
	int		i;
	t_data	*info;

	info = data;
	i = 0;
	while (i < info->philo)
	{
		sem_wait(info->done[i]);
		i++;
	}
	sem_wait(info->deathcheck);
	info->fin = 1;
	sem_post(info->deathcheck);
	return (NULL);
}

void	done_checker(t_data *info)
{
	pthread_create(&(info->finish), NULL, &done, info);
}

int		return_stats(t_data *info)
{
	int	i;

	i = 0;
	sem_wait(info->deathcheck);
	if (!info->fin && !info->dead)
		i = 1;
	sem_post(info->deathcheck);
	return(i);
}