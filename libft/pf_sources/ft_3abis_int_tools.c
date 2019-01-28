/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:55:35 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:35:27 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	ft_plus ajoute en debut de chaine de caractere le char c passe en parametre
** 	On l'utilise avec '+' si le flag->plus est setté
**	On l-utilise avec ' ' si flag->blank est setté et que != flag->plus
**	retourne la nouvelle chaine de caractere
*/

char		*ft_plus(t_chain *elem, char c)
{
	char	*show;
	char	*new;
	size_t	len_src;

	show = elem->show;
	len_src = ft_strlen(show);
	if (ft_is_decimal(elem->conv) && ft_tolower(elem->conv) != 'u')
	{
		if (show[0] != '-')
		{
			if (!(new = ft_strnew(len_src + 1)))
				return (show);
			new[0] = c;
			new = ft_strncat(new, show, len_src);
			free(show);
			return (new);
		}
	}
	return (show);
}

/*
**	ft_maj passe les caracteres ascii downcase de elem->show en uppercase
**	si ft_need_toupper retourne 1 (cf ft_recognize)
*/

char		*ft_maj(t_chain *elem)
{
	int		i;
	char	*show;

	show = elem->show;
	i = 0;
	if (ft_need_toupper(elem->conv))
	{
		while (show[i])
		{
			show[i] = ft_toupper(show[i]);
			i++;
		}
	}
	return (show);
}

/*
**	ft_0x_hexa ajoute a la chaine de caractere show un 0x en debut de chaine
**	afin de "signer" la base 16, (si 'X' on appliquera touuper par la suite)
*/

char		*ft_0x_hexa(char *show, char c, t_chain *elem)
{
	int		y;
	int		i;
	char	*new;
	int		res;

	res = ft_atoi_base_ll(show, 16);
	i = 0;
	y = 0;
	if (res == 0 && (ft_tolower(c) == 'x' || (c == 'p' && elem->give_p &&
					!elem->prec)))
		return (show);
	if (!(new = ft_strnew(ft_strlen(show) + 2)))
		return (NULL);
	new[i++] = '0';
	new[i++] = 'x';
	while (show[y])
		new[i++] = show[y++];
	free(show);
	return (new);
}

/*
**	ft_0_octal ajoute a la chaine de caractere show un 0 en debut de chaine
**	afin de "signer" la base 8
*/

char		*ft_0_octal(char *show)
{
	char	*new;
	int		y;
	int		i;

	i = 0;
	y = 0;
	if (ft_atoi_base_ll(show, 8) == 0)
		return (show);
	if (!(new = ft_strnew(ft_strlen(show) + 1)))
		return (NULL);
	new[i++] = '0';
	while (show[y])
		new[i++] = show[y++];
	free(show);
	return (new);
}

/*
**	ft_hash prend en parametre un maillon de la chaine
**	en fonction du char dans elem->conv on utilise la fonction correspondante
**	si x, X ou p => ft_0x_hexa
**	si o ou O => ft_0_octal
*/

char		*ft_hash(t_chain *elem)
{
	char	c;

	c = elem->conv;
	if (ft_tolower(c) == 'x' || elem->conv == 'p')
		return (ft_0x_hexa(elem->show, elem->conv, elem));
	else if (ft_tolower(c) == 'o')
		return (ft_0_octal(elem->show));
	return (elem->show);
}
