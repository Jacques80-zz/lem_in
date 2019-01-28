/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recognize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:07:44 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:38:40 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	ft_need_toupper nous indique si la sortie doit se faire en uppercase
*/

int		ft_need_toupper(char c)
{
	if (c == 'X' || c == 'E' || c == 'F' || c == 'G' || c == 'A')
		return (1);
	return (0);
}

/*
**	ft_get_base check si le caractere envoyé nous indique une base pour le nbr
**  de sortie, 16 pour les nbr en hexa et les pointeurs, 8 pr octal, 2 pr bin
*/

int		ft_get_base(char c)
{
	if (c == 'x' || c == 'X' || c == 'p')
		return (16);
	else if (c == 'o' || c == 'O')
		return (8);
	else if (c == 'b')
		return (2);
	return (10);
}

/*
**	Start digit renvoie la chaine de caractere qui contient le nb à partir du
**  premier chiffre souhaité (cad "enleve" les ox, Ox, -, +, 0 ou ' ' )
*/

char	*ft_start_digit(char *str, t_chain *elem)
{
	if (str[0] && str[1] && ft_tolower(elem->conv) != 'o')
	{
		if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
			return (&str[2]);
		else if (str[0] == '-' || str[0] == '+' ||
				str[0] == '0' || str[0] == ' ')
			return (&str[1]);
	}
	return (str);
}

/*
**	ft_is_integer check si le caractere passé en parametre nous indique que le
**  nbr donné est un entier
*/

int		ft_is_integer(char b)
{
	if (ft_tolower(b) == 'd' || b == 'i' || ft_tolower(b) == 'o'
					|| ft_tolower(b) == 'u' || ft_tolower(b) == 'x' || b == 'p')
		return (1);
	return (0);
}

/*
**	ft_is_decimal check si le caractere passé en parametre nous indique que le
**  nbr donné est un décimal
*/

int		ft_is_decimal(char b)
{
	if (ft_tolower(b) == 'd' || b == 'i' || ft_tolower(b) == 'e' || b == 'u'
					|| ft_tolower(b) == 'f' || ft_tolower(b) == 'g')
		return (1);
	return (0);
}
