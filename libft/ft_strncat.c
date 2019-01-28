/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 21:38:06 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/22 15:12:09 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	unsigned int		len;
	unsigned int		pos;

	len = 0;
	pos = 0;
	while (dest[len] != '\0')
		len++;
	while (pos < n && src[pos])
	{
		dest[pos + len] = src[pos];
		pos++;
	}
	dest[pos + len] = '\0';
	return (dest);
}
