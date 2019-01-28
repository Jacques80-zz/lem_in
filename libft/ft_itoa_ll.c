/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:44:26 by jdouniol          #+#    #+#             */
/*   Updated: 2018/10/30 13:44:30 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static long long	ft_get_expo(int len)
{
	long long	exp;

	exp = 1;
	while (len > 0)
	{
		exp = exp * 10;
		len--;
	}
	return (exp);
}

static int			ft_len_int(long long n)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char				*ft_itoa_ll(long long n)
{
	int			sign;
	ULL			x;
	long long	len;
	char		*res;
	int			y;

	y = 0;
	sign = (n < 0) ? 1 : 0;
	x = ABS(n);
	len = ft_len_int(x);
	if (!(res = ft_strnew(len + sign)))
		return (NULL);
	len = ft_get_expo(len - 1);
	if (sign)
		res[y++] = '-';
	while (len)
	{
		res[y++] = (x / len) + 48;
		x = x % len;
		len = len / 10;
	}
	return (res);
}
