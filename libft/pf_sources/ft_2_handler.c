/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:56:04 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:35:06 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	ft_putchar_w est utilise dans quand j'ai des wchar a afficher
**	j utilise strsub pour setter le byte avec le debut (1ere partie) du wchar
**	puis j'applique atoi base 2 pour setter nbr avec la valeur en binaire
**	je delete le *char byte et j'ecris l'adresse du nombre tant que i<len
*/

static int		ft_putchar_w(char *begin, int len)
{
	int		i;
	int		nbr;
	char	*byte;

	i = 0;
	byte = NULL;
	while (i < len && begin)
	{
		byte = ft_strsub(begin, i, 8);
		nbr = ft_atoi_base(byte, 2);
		ft_strdel(&byte);
		write(1, &(nbr), 1);
		i = i + 8;
	}
	return (0);
}

/*
**	ft_show_char_w est utilise des que ft_is_w_char renvoie 1.
**	si le flag left est active commence par putchar_w
**	puis ecrit space ()
**	Sinon, memset de i octets par c sur &elem->show puis putchar_w
*/

static int		ft_show_char_w(t_chain *elem)
{
	char			*space;
	int				i;
	char			c;

	i = 0;
	c = ((elem->flag)->zero) ? '0' : ' ';
	while (elem->show[i] == ' ')
		i++;
	if ((elem->flag)->left)
	{
		ft_putchar_w(elem->show, elem->nbr_byte * 8);
		space = &elem->show[elem->nbr_byte * 8];
		write(1, space, ft_strlen(space));
	}
	else
	{
		if (i)
		{
			write(1, ft_memset(elem->show, c, i), i);
		}
		ft_putchar_w(&elem->show[i], ft_strlen(&elem->show[i]));
	}
	return (1);
}

/*
**	Cas particulier du char null, soit le flag left est set et dans ce cas on
**	commence par ecrire "\0" puis elem->show
**	soit le flag left n'est pas set et on fini avec "\0".
*/

static int		ft_show_char_null(t_chain *elem)
{
	if (!elem->cnull && elem->conv == 'c' && elem->conv != 'l')
	{
		elem->nbr_carac = (elem->width > 0) ? elem->width : 1;
		if (!(elem->flag)->left)
		{
			write(1, elem->show, elem->nbr_carac - 1);
			write(1, "\0", 1);
			return (1);
		}
		else if ((elem->flag)->left)
		{
			write(1, "\0", 1);
			write(1, elem->show, elem->nbr_carac - 1);
			return (1);
		}
	}
	return (0);
}

/*
**	On appelle ft_show_all a chaque element de la liste chainee
**	on commence par deux cas d'erreur (cf plus haut)
**	puis le cas particulier des wild char
**	enfin, pour tous les autres cas, on affiche elem->show (sur x nbr carac)
**	le int total represente le sigma de tous les caracteres, tous maillons
**	confondus
**	Tant que elem->next != null, on repete l'operation
*/

int				ft_show_all(t_chain *elem)
{
	int			len;
	int			total;

	len = 0;
	total = 0;
	while (elem)
	{
		if (ft_show_char_null(elem) || ft_null_w_char(elem))
			;
		else if (elem->show && ft_is_w_char(elem))
			ft_show_char_w(elem);
		else if (elem->show)
		{
			elem->nbr_carac = ft_strlen(elem->show);
			write(1, elem->show, elem->nbr_carac);
		}
		total += elem->nbr_carac;
		elem = elem->next;
	}
	return (total);
}

/*
**	Si aucune erreur dans le parser, on enclenche ft_handler
**	Si l'application de la fonction elem->f renvoie -1, on applique
**	ft_show_error a l'element, sinon applique la fonction prevue
**	ensuite on affiche succesivement chaque maillon avec ft_show_all
**	on stoppe avec va_end la lecture de la liste d'arguments
**	on free la liste parcourue
*/

int				ft_handler(va_list ap, t_chain *chain)
{
	t_chain		*begin;
	int			total;

	begin = chain;
	while (chain)
	{
		if (!chain->just_show)
		{
			if (chain->f(chain, ap) == -1)
			{
				return (ft_show_error(chain, begin));
			}
		}
		chain = chain->next;
	}
	total = ft_show_all(begin);
	va_end(ap);
	ft_lstfree(begin);
	return (total);
}
