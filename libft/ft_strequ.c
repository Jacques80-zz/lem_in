/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:14:08 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:10:10 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Compare lexicographiquement s1 et s2. Si les deux chaines sont egales,
**	la fonction retourne 1, ou 0 sinon.
*/

int		ft_strequ(const char *s1, const char *s2)
{
	int x;

	if (s1 && s2)
	{
		x = ft_strcmp(s1, s2);
		if (x == 0)
			return (1);
	}
	return (0);
}
