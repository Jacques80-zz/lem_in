/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:07:28 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:38:12 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_prec_null_str_null(t_chain *elem)
{
	if (ft_strequ(elem->show, "(null)") && elem->prec == '0')
	{
		free(elem->show);
		return (1);
	}
	return (0);
}

/*
**	ft_prec_on_str gere la precision sur les chaines de caracteres
**	si null & prec a 0 via ft_prec_null_str_null, retourne une chaine de 1 \0
**	Si la precision est inferieure a strlen de elem->show prendre les 1ers char
**	de elem->show dans new
**	Set elem->nbr_carac avec strlen de new
**	Retourne new
**	Si prec superieure a strlen de elem->show, retourne elem->show
*/

static char	*ft_prec_on_str(t_chain *elem)
{
	char	*new;
	size_t	len;
	size_t	i;

	if (ft_prec_null_str_null(elem))
		return (ft_strnew(0));
	if (elem->prec < ft_strlen(elem->show))
	{
		i = 0;
		len = elem->prec;
		if (!(new = ft_strnew(len)))
			return (NULL);
		while (i < len)
		{
			new[i] = elem->show[i];
			i++;
		}
		elem->nbr_carac = ft_strlen(new);
		return (new);
	}
	return (elem->show);
}

/*
**	ft_prec_null_val_null gere les cas particulier ou le nbr et/ou prec = null
**	Pour un pointeur 'p' free elem->show et remplace par "0x"
**	Pour un decimal avec + ou blank free elem->show et remplace par '+' ou ' '
**	Pour octal sans hash free elem->show et retourne 1
*/

static int	ft_prec_null_val_null(t_chain *elem, t_flag *flag)
{
	int	base;

	base = ft_get_base(elem->conv);
	if (elem->prec == 0 && elem->give_p == 1 &&
			elem->conv == 'p' && ft_atoi_base_ll(elem->show, base) == 0)
	{
		free(elem->show);
		elem->show = ft_strdup("0x");
		return (0);
	}
	else if (elem->prec == 0 && ft_is_decimal(elem->conv) && (flag->plus == 1
				|| flag->blank == 1) && ft_atoi_base_ll(elem->show, base) == 0)
	{
		free(elem->show);
		elem->show = (flag->plus) ? ft_strdup("+") : ft_strdup(" ");
		return (0);
	}
	else if (elem->prec == 0 && !((elem->flag)->hash && ft_tolower(elem->conv)
				== 'o') && ft_atoi_base_ll(elem->show, base) == 0)
	{
		free(elem->show);
		return (1);
	}
	return (0);
}

/*
**	ft_prec_on_integer est appele a la fin de int_modifier si give_p est setté
**	On commence par mettre le flag 0 a 0
**	start_digit permet d'enlever le prefixe 0x ou 0 si besoin
**	Si la precision est inferieure ou egale a strlen du nombre cleané ou si
**	ft_strnew echoue retourne elem-show
**	Si la precision est superieure a strlen, on fait la diff du pointeur sur
**	tmp avec le debut de elem->show (pour connaitre le nombre de char a ecrire
**	au debut)
**	On ecrit d'abord ces char supp (' ', ou 0x, ou '+' ou '-')
**	puis on ajoute les zeros manquant
**	puis on ajoute enfin le nombre
*/

static char	*ft_prec_on_integer(t_chain *elem)
{
	char	*tmp;
	char	*new;
	long	i;
	long	y;

	i = 0;
	y = 0;
	(elem->flag)->zero = 0;
	if (ft_prec_null_val_null(elem, elem->flag))
		return (ft_strnew(0));
	tmp = ft_start_digit(elem->show, elem);
	if (elem->prec > ft_strlen(tmp))
	{
		if (!(new = ft_strnew(elem->prec + (tmp - elem->show))))
			return (elem->show);
		while (i < (tmp - elem->show))
			new[i++] = elem->show[y++];
		while ((UL)i < elem->prec - ft_strlen(tmp) + (tmp - elem->show))
			new[i++] = '0';
		while ((UL)i < elem->prec + (tmp - elem->show))
			new[i++] = elem->show[y++];
		free(elem->show);
		return (new);
	}
	return (elem->show);
}

/*
**	Si entier d, D, i, o, O, u, U, x, X, ou p, applique ft_prec_on_int
**	Si string sans conversion de type 'l', applique ft_prec_on_str
**	Si wstring donc 'S' ou 's' & 'l', applique ft_prec_on_w
** 	Elle est appelee a la fin de ft_int_modifier et ft_str_modifier
*/

char		*ft_precision(t_chain *elem)
{
	if (ft_is_integer(elem->conv))
		return (ft_prec_on_integer(elem));
	else if (elem->conv == 's' && elem->len != 'l')
		return (ft_prec_on_str(elem));
	else if (elem->conv == 'S' || (elem->len == 'l' && elem->conv == 's'))
		return (ft_prec_on_w(elem));
	return (elem->show);
}
