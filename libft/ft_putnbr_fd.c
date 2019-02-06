/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 22:20:04 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/13 22:24:42 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Affiche l'entier n sur le file descriptor.
*/

void	ft_putnbr_fd(int n, int fd)
{
	unsigned x;

	if (n < 0)
		ft_putchar_fd('-', fd);
	x = ft_absolute_int(n);
	if (n == 0)
		ft_putchar_fd('0', fd);
	else if (x > 0 && x < 10)
		ft_putchar_fd(x + 48, fd);
	else
	{
		ft_putnbr_fd(x / 10, fd);
		ft_putchar_fd((x % 10) + 48, fd);
	}
}
