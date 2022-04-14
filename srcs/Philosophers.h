/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:05:20 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/14 18:54:04 by wding-ha         ###   ########.fr       */
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
	pthread_mutex_t	deadlock;
	pthread_mutex_t	countlock;
	pthread_mutex_t checklock;
}				t_data;

typedef struct s_philo {
	pthread_t		thread;
	int				id;
	int				rfork;
	int				lfork;
	long long		last_eaten;
	int				die;
	t_data			*data;
}				t_philo;

void		build_info(t_data *info, char **argv, int argc);
void		*eat(void *args);
void		create_thread(t_data *info);
void		print_text(char *s, int state, int id, t_data *info);
void		destroy_mutex(t_data *info);
long long	get_milisec(void);
void		*death(void *arg);
void		eating_count(t_data *info);

#endif