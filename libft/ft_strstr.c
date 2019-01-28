/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 22:33:31 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/24 21:58:07 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strstr(const char *src, const char *to_find)
{
	char	*i1;
	char	*i2;

	if (!*to_find)
		return ((void *)src);
	while (*src)
	{
		if (*src == *to_find)
		{
			i1 = (void *)src + 1;
			i2 = (void *)to_find + 1;
			while (*i1 && *i2 && *i1 == *i2)
			{
				++i1;
				++i2;
			}
			if (!*i2)
				return ((void *)src);
		}
		src++;
	}
	return (NULL);
}
