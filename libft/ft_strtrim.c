/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:56:26 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:15:47 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Alloue avec malloc et retourne une copie de la chaine passee en
**	parametre sans les espaces blancs au debut et a la fin de cette chaine.
**	On considere comme des espaces blancs les caracteres ' ', '\n' et '\t'.
** 	Si s ne contient pas d'espaces blancs au debut ou a la fin, la fonction
**	renvoie une copie de s. Si l'allocation echoue, la fonction renvoie NULL.
*/

char	*ft_strtrim(char const *s)
{
	unsigned int	st;
	char			*new;
	int				end;

	st = 0;
	if (!s)
		return (NULL);
	end = (int)ft_strlen(s) - 1;
	while ((s[st] == ' ' || s[st] == '\n' || s[st] == '\t') && s[st])
		st++;
	while ((s[end] == ' ' || s[end] == '\t' ||
				s[end] == '\n') && s[end] && end > (int)st)
		end--;
	new = ft_strsub(s, st, (end - st + 1));
	if (!new)
		return (NULL);
	else
		return (new);
}
