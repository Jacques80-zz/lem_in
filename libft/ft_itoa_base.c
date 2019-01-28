/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:43:53 by jdouniol          #+#    #+#             */
/*   Updated: 2018/10/30 13:43:55 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Alloue avec malloc(3) et retourne une chaine de caracteres "fraiche"
**	terminee par un '\0' representatnt l'entier n passe en parametre.
**	La fonction prend un int comme base, valide de 2 à 16.
** 	Les nombres negatifs sont geres. Si l'allocation echoue, la fonction
**	renvoie NULL. Toutes les bases de 2 à 16 sont valides
*/

static int	ft_pow(unsigned int v, int base)
{
	if (v == 0)
		return (0);
	else
		return (1 + ft_pow(v / base, base));
}

char		*ft_itoa_base(unsigned int value, unsigned int base)
{
	char			*res;
	unsigned int	p;
	int				i;

	i = ft_pow(value, base);
	p = value;
	if (value == 0)
		i = 1;
	if (!(res = ft_strnew(i)) || base < 2 || base > 16)
		return (NULL);
	while (--i >= 0)
	{
		res[i] = (p % base < 10) ? p % base + 48 : p % base - 10 + 'a';
		p = p / base;
	}
	return (res);
}
