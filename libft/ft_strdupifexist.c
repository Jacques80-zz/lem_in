/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupifexist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:46:50 by jdouniol          #+#    #+#             */
/*   Updated: 2018/10/30 13:46:52 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdupifexist(const char *str)
{
	char	*copy;
	int		strlen;
	char	*origin;

	if (!str)
		return (NULL);
	strlen = 0;
	while (str[strlen])
		strlen++;
	if (!(copy = (char *)malloc(sizeof(char) * (strlen + 1))))
		return (NULL);
	origin = copy;
	while (*str)
	{
		*copy++ = *str++;
	}
	*copy = '\0';
	return (origin);
}
