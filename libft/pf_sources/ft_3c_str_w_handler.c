/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_w_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:08:10 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:36:12 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	ft_null_w_char commence par cleaner avce strtrim elem->show
**	Si null, et pas de flag left, on ecrit d'abord sur width -1 puis "\0"
**	Si null et flag left on ecrit "\0" puis elem->show
**	elem->nbr_carac = width si superieure a 0 sinon 1. puis on free byte
*/

int				ft_null_w_char(t_chain *elem)
{
	char	*byte;

	if ((elem->conv == 'C' || (elem->conv == 'c' && elem->len == 'l')))
	{
		byte = ft_strtrim(elem->show);
		if (ft_strequ(byte, "0"))
		{
			if (!(elem->flag)->left && elem->width > 0)
				write(1, elem->show, elem->width - 1);
			write(1, "\0", 1);
			if ((elem->flag)->left && elem->width > 0)
				write(1, elem->show, elem->width - 1);
			elem->nbr_carac = (elem->width > 0) ? elem->width : 1;
			free(byte);
			return (1);
		}
		free(byte);
		return (0);
	}
	return (0);
}

/*
**	ft_is_w_char retourne 1 si nous souhaitons traiter les arguments en wchar
**	donc pour tous les cas suivants: 'c' & 'l' ou 's' & 'l' ou 'S' ou 'C'
*/

int				ft_is_w_char(t_chain *elem)
{
	if (elem->conv == 'c' && elem->len == 'l')
		return (1);
	else if (elem->conv == 's' && elem->len == 'l')
		return (1);
	else if (elem->conv == 'S' || elem->conv == 'C')
		return (1);
	return (0);
}

/*
**	ft_w_char_handler retourne sous forme de chaine de caracteres chaque wchar
** 	qu'on lui envoie en parametre
** 	On lit la valeur en int du wc grace au byte de poids fort
**	on commence avec la gestion d'erreur des caracteres utf8 non valides
**	si wc <= a 127 il tient sur 1 byte on utilise ft_one_byte
**	si 127 < wc < 256 et MB = 1, on doit utiliser ft_itoa_base avec base 2
**	si il s'agit d'une str et que la prec est inferieure a strlen ft_itoa_base2
**	si wc <= 2047 et MB > 1 => ft_two_bytes
**	si wc <= 65535 et MB > 2 => ft_three_bytes
**	si wc <= 1114111 et MB > 3 => ft_four_bytes
**	On finit en settant elem->nbr_carac avec l'ajout de strlen(bin) + subtilite
*/

static char		*ft_w_char_handler(wchar_t wc, t_chain *elem)
{
	char			*bin;

	bin = NULL;
	if (!(wc <= 0x10ffff && wc >= 0 && (wc <= 0xd7ff || wc >= 0xe000)) &&
			(MB_CUR_MAX != 1 || ft_tolower(elem->conv) == 'c'))
		return (NULL);
	if (wc <= 127 && MB_CUR_MAX > 0)
		bin = ft_one_byte(wc);
	else if (wc > 127 && wc < 256 && MB_CUR_MAX == 1)
		bin = ft_itoa_base(wc, 2);
	else if (MB_CUR_MAX == 1 && ft_tolower(elem->conv) == 's')
	{
		if (elem->prec < (ft_strlen(elem->show) / 8) + 1 && elem->give_p)
			bin = ft_itoa_base(wc, 2);
	}
	else if (wc <= 2047 && MB_CUR_MAX > 1)
		bin = ft_two_bytes(wc);
	else if (wc <= 65535 && MB_CUR_MAX > 2)
		bin = ft_three_bytes(wc);
	else if (wc <= 1114111 && MB_CUR_MAX > 3)
		bin = ft_four_bytes(wc);
	if (bin)
		elem->nbr_carac += (ft_strlen(bin) / 8 == 0) ? 1 : ft_strlen(bin) / 8;
	return (bin);
}

/*
**	ft_str_big_s_handler est appele pour 'S' ou 's' & 'l'
**	si le caractere est null, set les differents elements de la structure
**	(show, nbr_carac, conv et len)
**	sinon ajoute les uns a la suite des autres via strjoin_clr et
**	ft_w_char_handler
*/

static int		ft_str_big_s_handler(t_chain *elem, va_list ap)
{
	wchar_t		*sw;

	sw = va_arg(ap, wchar_t *);
	if (!sw)
	{
		elem->show = ft_strdup("(null)");
		elem->nbr_carac = ft_strlen(elem->show);
		elem->conv = 's';
		elem->len = 0;
	}
	else
	{
		elem->show = ft_strnew(0);
		while (*sw)
		{
			if (!(elem->show = ft_strjoin_clr(elem->show,
							ft_w_char_handler(*sw, elem))))
				return (-1);
			sw++;
		}
	}
	return (1);
}

/*
**	ft_str_w_handler prend en parametre un element de la liste ainsi que le
**	va_arg correspondant.
**	Si 'C' ou 'c' avec conversion 'l' on appelle ft_w_char_handler
**	Si 'S' ou 's' avec conversion 'l' on appelle ft_str_big_s_handler
**	On fini en appelant ft_str_modifier qui prend en parametre l'element et les
**	flags de la structure correspondante
*/

int				ft_str_w_handler(t_chain *elem, va_list ap)
{
	int			res;

	if (elem->conv == 'C' || (elem->conv == 'c' && elem->len == 'l'))
	{
		if (!(elem->show = ft_w_char_handler(va_arg(ap, wchar_t), elem)))
			return (-1);
	}
	else if (elem->conv == 'S' || (elem->conv == 's' && elem->len == 'l'))
		if ((res = ft_str_big_s_handler(elem, ap)) == -1)
			return (-1);
	elem->nbr_byte = elem->nbr_carac;
	return (ft_str_modifier(elem, elem->flag));
}
