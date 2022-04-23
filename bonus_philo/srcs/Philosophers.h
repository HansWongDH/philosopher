/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:05:20 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/23 22:06:56 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include "libft.h"
# include "color.h"

typedef struct s_data {
	int				philo;
	int				death;
	int				eat;
	int				sleep;
	int				timeleft;		
	long long		*last_eaten;
	int				dead;
	pid_t			*pid;
	sem_t			**sem;
	sem_t			**monitor;
	sem_t			*print;
	sem_t			*start;
	sem_t			*done;
}				t_data;

typedef struct s_philo {
	int				pid;
	int				id;
	int				rfork;
	int				lfork;
	int				eaten;
	t_data			*data;
}				t_philo;

int			input_checking(char **av, int ac);
void		build_info(t_data *info, char **argv, int argc);
int			fork_creation(t_data *info);
void		print_text(char *s, char *c, int id, t_data *info);
long long	get_ms(void);
void		ft_msleep(int time, long long start);
int			ft_malloc(void **ptr, size_t size);
sem_t		*ft_sem_create(char *str, int i);
void		sem_kill(t_data *info);
void		wait_for_my_child(t_data info);
void		*death(void *arg);
void		freestruct(t_data *info);
int			error(int i);
void		sem_unchain(t_data *info);
void		freestruct(t_data *info);

#endif