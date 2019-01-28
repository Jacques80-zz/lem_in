/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:06:26 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/26 06:06:27 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Prend en parametre l’adresse d’un pointeur dont la zone pointee doit etre
**	liberee avec free(3), puis le pointeur est mis a NULL.
*/

void	ft_memdel(void **ap)
{
	if (ap && *ap)
	{
		free(*ap);
		*ap = NULL;
	}
}
