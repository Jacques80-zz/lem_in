/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:12:24 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/20 22:00:37 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*darray;
	unsigned char	*sarray;

	darray = dest;
	sarray = (void*)src;
	while (n--)
		*darray++ = *sarray++;
	return (dest);
}
