/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:06:27 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:35:16 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	ft_int_modifier est appele a la fin des handler pour chaque element
**	on checke successivement les flags '+', ' ', '#', 'maj', 'prec' et'largeur'
**	On applique succesivement les fonctions correspondantes cf ft_int_tools
*/

static int		ft_int_modifier(t_chain *elem)
{
	t_flag	*flag;

	flag = elem->flag;
	if (flag->plus)
		elem->show = ft_plus(elem, '+');
	if (!flag->plus && flag->blank)
		elem->show = ft_plus(elem, ' ');
	if (flag->hash || elem->conv == 'p')
		elem->show = ft_hash(elem);
	if (elem->maj)
		elem->show = ft_maj(elem);
	if (elem->give_p)
		elem->show = ft_precision(elem);
	if (elem->width > ft_strlen(elem->show))
		elem->show = ft_width(elem, flag);
	return (1);
}

/*
**	ft_int_handler prend en parametre un elem int de la chaine
**	il ecrit dans une str new et dans elem->show fonction de la presence ou non
**	d'une conversion de type, au besoin on cast l'argument
**	On applique ft_int_modifier en fin de fonction
*/

int				ft_int_handler(t_chain *elem, va_list ap)
{
	char	*new;

	new = NULL;
	if ((!elem->len || elem->len == 'L') && elem->conv != 'D')
		new = ft_itoa(va_arg(ap, int));
	else if (elem->len == 'h' && elem->conv != 'D')
		new = ft_itoa_ll((short)va_arg(ap, int));
	else if (elem->len == 'H' && elem->conv != 'D')
		new = ft_itoa((char)va_arg(ap, int));
	else if (elem->len == 'l' || elem->conv == 'D')
		new = ft_itoa_ll(va_arg(ap, long));
	else if (elem->len == 'm')
		new = ft_itoa_ll(va_arg(ap, long long));
	else if (elem->len == 'j')
		new = ft_itoa_ll(va_arg(ap, intmax_t));
	else if (elem->len == 'z')
		new = ft_itoa_ll(va_arg(ap, ssize_t));
	if (new)
		elem->show = new;
	else
		elem->show = ft_strnew(0);
	return (ft_int_modifier(elem));
}

/*
**	ft_exception_uint nous permet de savoir si la conversion de base accepte
**	le cast qu'on s'apprete a faire, si U, O ou P renvoie 1 sinon 0
*/

static int		ft_exception_uint(char c)
{
	if (c == 'U' || c == 'O' || c == 'p')
		return (1);
	return (0);
}

/*
**	ft_uint_handler prend en parametre un elem unsigned int de la chaine
**	il ecrit dans une str new et dans elem->show fonction de la presence ou non
**	d'une conversion de type, au besoin on cast l'argument
**	On applique ft_int_modifier en fin de fonction
*/

int				ft_uint_handler(t_chain *elem, va_list ap)
{
	char		*new;
	int			base;

	new = NULL;
	base = ft_get_base(elem->conv);
	if (elem->len == 'h' && !ft_exception_uint(elem->conv))
		new = ft_itoa_base((unsigned short)va_arg(ap, unsigned int), base);
	else if (elem->len == 'H' && !ft_exception_uint(elem->conv))
		new = ft_itoa_base((unsigned char)va_arg(ap, unsigned int), base);
	else if (elem->len == 'l' || ft_exception_uint(elem->conv))
		new = ft_itoa_base_ll(va_arg(ap, UL), base);
	else if (elem->len == 'm')
		new = ft_itoa_base_ll(va_arg(ap, ULL), base);
	else if (elem->len == 'j')
		new = ft_itoa_base_ll(va_arg(ap, uintmax_t), base);
	else if (elem->len == 'z')
		new = ft_itoa_base_ll(va_arg(ap, size_t), base);
	else
		new = ft_itoa_base(va_arg(ap, unsigned int), base);
	if (new)
		elem->show = new;
	else
		elem->show = ft_strnew(0);
	return (ft_int_modifier(elem));
}
