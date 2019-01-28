/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:55:30 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:12:06 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Ajoute un retour à la ligne à la fin de la chaine passée en paramètre et
** 	écrit le tout sur le file descriptor passé en paramètre.
*/

void	ft_putendl_fd(char const *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
