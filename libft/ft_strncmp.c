/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:04:22 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/25 22:45:27 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*c1;
	unsigned char	*c2;

	if (!n)
		return (0);
	i = 0;
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (i < n)
	{
		if (c1[i] != c2[i] || c1[i] == '\0')
			return (c1[i] - c2[i]);
		i++;
	}
	return (0);
}
