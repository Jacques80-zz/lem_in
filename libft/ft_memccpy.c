/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:58:22 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/20 21:58:31 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*darray;
	unsigned char		*sarray;
	unsigned char		find;

	darray = (unsigned char *)dst;
	sarray = (unsigned char *)src;
	find = (unsigned char)c;
	while (n--)
	{
		*darray = *sarray;
		if (*sarray == find)
			return (++darray);
		sarray++;
		darray++;
	}
	return (NULL);
}
