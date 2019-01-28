/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 21:54:19 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:06:42 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Affiche une chaine de caractères passée en paramètre sur la sortie standard
*/

void	ft_putstr(char const *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}
