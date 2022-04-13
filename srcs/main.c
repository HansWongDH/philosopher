/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:50:04 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/13 19:22:39 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	main(int argc, char **argv)
{
	t_data		info;
	int			i;

	if (argc != 5 && argc != 6)
		return (0);
	if (argc == 5)
		build_info(&info, argv);
	i = 0;
	info.lock = malloc(sizeof(pthread_mutex_t *) * info.philo);
	while (i < info.philo)
		pthread_mutex_init(&(info.lock[i++]), NULL);
	create_thread(&info);
	destroy_mutex(&info);
}
