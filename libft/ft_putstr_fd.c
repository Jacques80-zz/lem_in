/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 22:26:46 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:08:22 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <unistd.h>

/*
**	Affiche la chaine de caractères c sur le file descriptor passé en paramètre
*/

void	ft_putstr_fd(char const *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			ft_putchar_fd(*s, fd);
			s++;
		}
	}
}
