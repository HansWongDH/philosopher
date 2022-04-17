/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:05:20 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/17 20:26:17 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include "libft.h"
# include "color.h"

typedef struct s_data {
	int				philo;
	int				death;
	int				eat;
	int				sleep;
	int				timeleft;		
	int				dead;
	int				done;
	pthread_mutex_t	*lock;
	pthread_mutex_t	print;
	pthread_mutex_t	checklock;
}				t_data;

typedef struct s_philo {
	pthread_t		thread;
	int				id;
	int				rfork;
	int				lfork;
	long long		last_eaten;
	int				eaten;
	t_data			*data;
}				t_philo;

void		build_info(t_data *info, char **argv, int argc);
void		*action(void *args);
void		create_thread(t_data *info);
void		print_text(char *s, char *c, int id, t_data *info);
void		destroy_mutex(t_data *info);
long long	get_milisec(void);
void		*death(void *arg);
void		self_sleep(int time);

#endif