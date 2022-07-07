/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:51:19 by wding-ha          #+#    #+#             */
/*   Updated: 2022/07/07 18:19:37 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

/*	
	1. Input checking, filter out invalid input;
	2. Initialized main struct t_data;
	3. pass the struct to fork_creation to generate philo;
	4. initilize death checker to monitor philo using main process;
	5. remove all the semaphore & free memory;
*/

void	waitforpid(t_data *info)
{
	int	ex;
	int	i;

	i = 0;
	while (i < info->philo)
	{
		waitpid(-1, &ex, 0);
		if (WEXITSTATUS(ex) != 0)
		{
			kill_child(info);
			break ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		info;

	if (argc != 5 && argc != 6)
		return (error(0));
	if (!input_checking(argv, argc))
		return (0);
	build_info(&info, argv, argc);
	fork_creation(&info);
	waitforpid(&info);
	sem_kill(&info);
	exit (0);
}
