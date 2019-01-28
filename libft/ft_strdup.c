/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 18:35:12 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/16 19:19:39 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	La fonction strdup() renvoie un pointeur sur une nouvelle chaîne de
**	caractères qui est dupliquée depuis s. La mémoire occupée par cette
**	nouvelle chaîne est obtenue en appelant malloc(3), et peut (doit) donc
**	être libérée avec free(3).
*/

char	*ft_strdup(const char *str)
{
	char	*copy;
	int		strlen;
	char	*origin;

	strlen = 0;
	while (str[strlen])
		strlen++;
	if (!(copy = (char *)malloc(sizeof(char) * (strlen + 1))))
		return (NULL);
	origin = copy;
	while (*str)
	{
		*copy++ = *str++;
	}
	*copy = '\0';
	return (origin);
}
