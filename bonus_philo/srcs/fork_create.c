/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:25:15 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/19 22:35:22 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

sem_t *ft_sem_create(int i)
{
	char	*str;
	sem_t	*sem;

	str = ft_itoa(i);
	sem = sem_open(str, O_CREAT, 0664, 1);
	return (sem);
}