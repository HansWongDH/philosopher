/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:34:35 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/22 21:08:42 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	print_text(char *s, char *c, int id, t_data *info)
{
	sem_wait(info->print);
	if (info->dead == 0)
		printf("%s%lld\tPhilosopher %d\t%s", c, get_ms(), id, s);
	sem_post(info->print);
}
