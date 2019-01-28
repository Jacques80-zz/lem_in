/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:40:13 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:14:16 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Alloue avec malloc et retourne la copie "fraiche" d'un troncon de la
** 	chaine de caracteres passee en parametre. Le troncon commence a l'index
** 	start et a pour longueur len. Si start et len ne designent pas un troncon
**	de chaine valide, le comportement est indetermine. Si l'allocation echoue,
**	la fonction renvoie NULL.
*/

#include "../includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*c;

	if (!s || !(c = ft_strnew(len)))
		return (NULL);
	while (start--)
		s++;
	ft_strncpy(c, s, len);
	c[len] = '\0';
	return (c);
}
