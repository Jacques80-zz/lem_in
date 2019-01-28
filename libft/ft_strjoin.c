/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:48:49 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:14:57 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Alloue avec malloc et retourne une chaine de caracteres "fraiche"
**	terminee pas un '\0' resultant de la concatenation de s1 et s2. Si
**	l'allocation echoue, la fonction renvoie NULL.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len1;
	unsigned int	len2;
	char			*new;
	char			*cnew;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(new = ft_strnew(len1 + len2)))
		return (NULL);
	cnew = new;
	while (*s1)
		*new++ = *s1++;
	while (*s2)
		*new++ = *s2++;
	*new = '\0';
	return (cnew);
}
