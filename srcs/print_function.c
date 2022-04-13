/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:34:35 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/13 19:45:48 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"
#include "color.h"

void	print_text(char *s, int state, int id, t_data *info)
{
	char	*c;

	pthread_mutex_lock(&(info->print));
	if (state == 0)
		c = CYAN;
	if (state == 1)
		c = YELLOW;
	if (state == 2)
		c = GREEN;
	if (state == 3)
		c = BLUE;
	if (state == 4)
		c = RED;
	printf("%s%lld Philosopher %d %s", c, get_milisec(), id, s);
	pthread_mutex_unlock(&(info->print));
}
