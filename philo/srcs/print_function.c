/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:34:35 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/18 13:14:41 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	print_text(char *s, char *c, int id, t_data *info)
{
	pthread_mutex_lock(&(info->print));
	if (info->dead == 0)
		printf("%s%lld Philosopher %d %s", c, get_milisec(), id, s);
	pthread_mutex_unlock(&(info->print));
}
