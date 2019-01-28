/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:47:40 by jdouniol          #+#    #+#             */
/*   Updated: 2018/10/30 13:47:42 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim_c(char const *s, char c)
{
	unsigned int	st;
	char			*new;
	int				end;

	st = 0;
	if (!s)
		return (NULL);
	end = (int)ft_strlen(s) - 1;
	while ((s[st] == c || s[st] == '\n' || s[st] == '\t') && s[st])
		st++;
	while ((s[end] == c || s[end] == '\t' ||
				s[end] == '\n') && s[end] && end > (int)st)
		end--;
	new = ft_strsub(s, st, (end - st + 1));
	if (!new)
		return (NULL);
	else
		return (new);
}
