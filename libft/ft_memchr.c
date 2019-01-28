/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:18:37 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/22 15:09:36 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned int	i;
	unsigned char	ch;
	unsigned char	*cstr;

	cstr = (unsigned char *)str;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (cstr[i] == ch)
			return (cstr + i);
		i++;
	}
	return (NULL);
}
