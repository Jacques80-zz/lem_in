/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:01:06 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/24 22:06:14 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int h;
	unsigned int n;
	unsigned int turn;

	turn = 0;
	n = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[turn] && turn < len)
	{
		h = turn;
		while (haystack[h] == needle[n] && haystack[h] && needle[n] && h < len)
		{
			if (needle[n + 1] == '\0')
				return ((char *)haystack + turn);
			h++;
			n++;
		}
		n = 0;
		turn++;
	}
	return (NULL);
}
