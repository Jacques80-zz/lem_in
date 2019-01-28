/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_roman.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:12:05 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:37:52 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*ft_roman_cent(int nb)
{
	int		tmp;
	char	*cent[10];
	char	*str;

	cent[0] = "\0";
	cent[1] = "C\0";
	cent[2] = "CC\0";
	cent[3] = "CCC\0";
	cent[4] = "CD\0";
	cent[5] = "D\0";
	cent[6] = "DC\0";
	cent[7] = "DCC\0";
	cent[8] = "DCCC\0";
	cent[9] = "CM\0";
	tmp = (nb % 1000) / 100;
	str = cent[tmp];
	return (str);
}

char	*ft_roman_ten(int nb)
{
	int		tmp;
	char	*ten[10];
	char	*str;

	ten[0] = "\0";
	ten[1] = "X\0";
	ten[2] = "XX\0";
	ten[3] = "XXX\0";
	ten[4] = "XL\0";
	ten[5] = "L\0";
	ten[6] = "LX\0";
	ten[7] = "LXX\0";
	ten[8] = "LXXX\0";
	ten[9] = "XC\0";
	tmp = ((nb % 1000) % 100) / 10;
	str = ten[tmp];
	return (str);
}

char	*ft_roman_unit(int nb)
{
	int		tmp;
	char	*unit[10];
	char	*str;

	unit[0] = "\0";
	unit[1] = "I\0";
	unit[2] = "II\0";
	unit[3] = "III\0";
	unit[4] = "IV\0";
	unit[5] = "V\0";
	unit[6] = "VI\0";
	unit[7] = "VII\0";
	unit[8] = "VIII\0";
	unit[9] = "IX\0";
	tmp = (((nb % 1000) % 100) % 10) / 1;
	str = unit[tmp];
	return (str);
}

/*
**	ft_roman_handler est appelé quand 'B' est passé en conversion
**	elle se base sur 3 tableaux de 10 char* qui contiennent respectivement
**	les centaines, les dizaines et les unités
** 	On ecrit le tout dans une str qui commence par le modulo des milliers
**	on ajoute a cette str la correspondance de chacun des trois tableaux
**	avec strcat
*/

int		ft_roman_handler(t_chain *elem, va_list ap)
{
	char	*str;
	int		tmp;
	int		l;
	int		m;

	m = 0;
	tmp = va_arg(ap, int);
	l = tmp / 1000;
	str = ft_strnew(0);
	if (!(str = (char *)malloc(sizeof(char) * (l + 16))))
		return (0);
	while (l != 0)
	{
		str = ft_strcat(str, "M\0");
		l--;
		m++;
	}
	str = ft_strcat(str, ft_roman_cent(tmp));
	str = ft_strcat(str, ft_roman_ten(tmp));
	str = ft_strcat(str, ft_roman_unit(tmp));
	elem->show = str;
	return (0);
}

/*
**	ft_binary_handler est appelé quand 'b' est passé en conversion
**	elle transforme un int passé "en parametre" en chaine de caractere
**	qui represente sa conversion en nombre binaire, on ajoute \0 à la fin
**	avec strtcat
*/

int		ft_binary_handler(t_chain *elem, va_list ap)
{
	char	*str;
	int		nb;

	nb = va_arg(ap, int);
	str = ft_itoa_base(nb, 2);
	ft_strcat(str, "\0");
	elem->show = str;
	return (0);
}
