/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 21:21:18 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/11 21:34:26 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int		len;
	int		pos;

	len = 0;
	pos = 0;
	while (dest[len] != '\0')
		len++;
	while (src[pos] != '\0')
	{
		dest[pos + len] = src[pos];
		pos++;
	}
	dest[pos + len] = '\0';
	return (dest);
}
