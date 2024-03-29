/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:14:38 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/20 21:57:59 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char *ch;

	if (!(str))
		return;
	ch = (unsigned char *)str;
	while (n--)
	{
		*ch = '\0';
		ch++;
	}

}
