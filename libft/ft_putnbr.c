/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 21:58:44 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/13 22:13:40 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Affiche l'entier n sur la sortie standard.
*/

void	ft_putnbr(int n)
{
	unsigned x;

	if (n < 0)
		ft_putchar('-');
	x = ft_absolute_int(n);
	if (n == 0)
		ft_putchar('0');
	else if (x > 0 && x < 10)
		ft_putchar(x + 48);
	else
	{
		ft_putnbr(x / 10);
		ft_putchar((x % 10) + 48);
	}
}
