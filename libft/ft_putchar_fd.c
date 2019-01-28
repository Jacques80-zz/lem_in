/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 22:14:23 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:07:33 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Affiche le caractere c sur le file descriptor passé en paramètre.
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
