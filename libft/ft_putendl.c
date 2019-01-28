/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:46:04 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:11:31 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Ajoute un retour à la ligne à la fin de la chaine passée en paramètre et
** 	écrit le tout sur la sortie standard
*/

void	ft_putendl(char const *s)
{
	if (s)
	{
		ft_putstr(s);
		ft_putchar('\n');
	}
}
