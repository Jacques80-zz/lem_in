/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:14:08 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:10:30 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Compare lexicographiquement s1 et s2 jusqu’a n caracteres maximum ou bien
**	qu’un ’\0’ ait ete rencontre. Si les deux chaines sont egales, la fonction
**	retourne 1, ou 0 sinon.
*/

int		ft_strnequ(const char *s1, const char *s2, size_t n)
{
	int	x;

	if (s1 && s2)
	{
		x = ft_strncmp(s1, s2, n);
		if (x == 0)
			return (1);
	}
	return (0);
}
