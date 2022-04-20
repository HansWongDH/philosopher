/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:25:15 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/20 18:54:00 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

sem_t	*ft_sem_create(int i)
{
	char	*str;
	sem_t	*sem;

	str = ft_itoa(i);
	sem = sem_open(str, O_CREAT, 0664, 1);
	return (sem);
}


void	fork_creation(t_data *info)
{
	t_philo		*ph;
	int			i;

	i = 0;
	ph = malloc(sizeof(t_philo) * info->philo);
	while (i < info->philo)
	{
		ph[i].id = i;
		ph[i].data = info;
		ph[i].rfork = ft_itoa(i);
		ph[i].lfork = ft_itoa((i + 1) % info->philo);
		ph[i].last_eaten = get_ms();
		ph[i].eaten = info->timeleft;
		ph[i].pid = fork();
		i++;
	}
	i = 0;
	while (i < info->philo)
	{
		if (ph[i].pid == 0)
			printf("id %d pid %d, rfork %s, lfork%s\n", ph[i].id, ph[i].pid, ph[i].rfork, ph[i].lfork);
		i++;
	}
	free(ph);
}