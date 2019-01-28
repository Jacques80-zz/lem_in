/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:45:12 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/20 21:21:21 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Alloue avec malloc(3) et retourne une zone de memoire "fraiche". La memoire
**	allouee est intialisee a 0. Si l'allocation echoue, la fonction renvoie
**	NULL.
*/

void	*ft_memalloc(size_t size)
{
	void	*tab;

	if (!(tab = (void *)malloc(sizeof(void) * size)))
		return (NULL);
	ft_bzero(tab, size);
	return (tab);
}
