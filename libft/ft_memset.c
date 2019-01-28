/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 16:53:18 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/24 21:10:36 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char *ch;

	ch = (unsigned char *)str;
	while (n--)
	{
		*ch = (unsigned char)c;
		ch++;
	}
	return (str);
}
