/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_libs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:21:55 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/11 17:26:47 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	ft_intlen(long n, int sign)
{
	int	len;

	len = 0;
	if (sign < 0)
		len = 1;
	if (n == 0)
		len += 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	*ft_calloc(size_t num, size_t size)
{
	int		tol;
	void	*ret;
	int		i;

	tol = num * size;
	ret = malloc(num * size);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < tol)
	{
		((char *)ret)[i] = '\0';
		i++;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	int		i;
	int		sign;
	char	*hold;
	long	num;

	sign = 1;
	num = (long)n;
	if (num < 0)
		sign *= -1;
	num *= sign;
	i = ft_intlen(num, sign);
	hold = ft_calloc(i + 1, 1);
	if (!hold)
		return (NULL);
	if (sign < 0)
		hold[0] = '-';
	if (n == 0)
		hold[0] = '0';
	while (num)
	{
		hold[i-- - 1] = '0' + (num % 10);
		num /= 10;
	}
	return (hold);
}
