/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 21:50:37 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/22 15:11:43 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	lendst;
	size_t	lensrc;

	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	if (len <= lendst)
		return (lensrc + len);
	while (*dst && len-- > 1)
		dst++;
	while (*src && len-- > 1)
		*dst++ = *src++;
	*dst = '\0';
	return (lensrc + lendst);
}
