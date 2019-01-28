/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:38:29 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/26 02:36:04 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Alloue avec malloc(3) et retourne une chaine de caractere “fraiche”
**	terminee par un ’\0’. Chaque caractere de la chaine est initialise a ’\0’.
**	Si l’allocation echoue, la fonction renvoie NULL.
*/

char	*ft_strnew(size_t size)
{
	return ((char *)ft_memalloc(size + 1));
}
