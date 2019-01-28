/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_clr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:47:10 by jdouniol          #+#    #+#             */
/*   Updated: 2018/10/30 13:47:12 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Alloue avec malloc et retourne une chaine de caracteres "fraiche"
**	terminee par un '\0' resultant de la concatenation de s1 et s2. Si
**	l'allocation echoue, la fonction renvoie NULL.
**	A la fin free s1 et s2.
*/

char	*ft_strjoin_clr(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	y;
	char			*new;
	char			*cnew;

	i = 0;
	y = 0;
	if (!s1 || !s2)
	{
		free(s2);
		free(s1);
		return (NULL);
	}
	if (!(new = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	cnew = new;
	while (s1[i])
		*new++ = s1[i++];
	while (s2[y])
		*new++ = s2[y++];
	*new = '\0';
	free(s1);
	free(s2);
	return (cnew);
}
