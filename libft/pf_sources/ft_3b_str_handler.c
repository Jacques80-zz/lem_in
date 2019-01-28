/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:07:59 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:35:59 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	ft_str_modifier est appelé à la fin de str handler et str_w_handler
**	si il n'y a rien a afficher il retourne 0, sinon si precision et que
**	la conv n'est pas 'c', il applique ft_precision à l'element
**	puis si la largeur est supérieure au nbr de caractere, applique la fonction
**	ft`width qui peut prendre en parametre egalement les flags
*/

int		ft_str_modifier(t_chain *elem, t_flag *flag)
{
	if (!elem->show)
		return (0);
	if (elem->give_p && elem->conv != 'c')
		elem->show = ft_precision(elem);
	if (elem->width > elem->nbr_carac)
		elem->show = ft_width(elem, flag);
	return (1);
}

/*
**	ft_str_handler est appelé pour 's' et 'c'
**	si la conversion de type est 'l' on appelle str_w_handler
**	Pour 's' si le petit malin m'envoie null on renvoie null merci curqui
**	On set elem->nbr_carac sur strlen de de elem->show
**	Pour 'c' pareil pour null, on copie va_arg dans c via sa valeur ascii
**	On set nbr_carac à 1
**	Si on est rentré dans aucun des trois, elem->show de 1 caractere \0
**	A la fin on appelle ft_str_modifier
*/

int		ft_str_handler(t_chain *elem, va_list ap)
{
	char		c;

	if (elem->len == 'l')
		return (ft_str_w_handler(elem, ap));
	else if (elem->conv == 's')
	{
		if (!(elem->show = ft_strdupifexist(va_arg(ap, char *))))
			elem->show = ft_strdup("(null)");
		elem->nbr_carac = ft_strlen(elem->show);
	}
	else if (elem->conv == 'c')
	{
		c = va_arg(ap, int);
		if (c == '\0')
			elem->cnull = 0;
		elem->show = ft_strnew(elem->cnull);
		elem->show[0] = c;
		elem->nbr_carac = 1;
	}
	else
		elem->show = ft_strnew(0);
	return (ft_str_modifier(elem, elem->flag));
}
