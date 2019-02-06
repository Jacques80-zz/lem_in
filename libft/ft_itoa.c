/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 23:13:00 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/26 04:26:50 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Alloue avec malloc(3) et retourne une chaine de caracteres "fraiche"
**	terminee par un '\0' representatnt l'entier n passe en parametre. Les
**	nombres negatifs sont geres. Si l'allocation echoue, la fonction
**	renvoie NULL.
*/

static int		ft_get_expo(int len)
{
	int exp;

	exp = 1;
	while (len > 0)
	{
		exp = exp * 10;
		len--;
	}
	return (exp);
}

static int		ft_len_int(int n)
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

char			*ft_itoa(int n)
{
	int				sign;
	unsigned int	x;
	int				len;
	char			*res;
	int				y;

	y = 0;
	sign = (n < 0) ? 1 : 0;
	x = ft_absolute_int(n);
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
