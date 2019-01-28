/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_ft_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:52:04 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:32:13 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	Pour chaque element qui ne contient pas de noeud (%), on set le
**	parametre de notre element just show a 1, nb carac avec len
**	et show avec ft_strsub avec start a 0 et size de len
**	Si strsub ou create elem echoue, retourne 0
**	si ok, ajoute l'elem a la suite des autres
*/

int				ft_show_only_parser(const char *format, size_t len, t_chain **c)
{
	char		*new;
	t_chain		*elem;

	if (!(new = ft_strsub(format, 0, len)))
		return (0);
	if (!(elem = ft_create_elem()))
		return (0);
	elem->just_show = 1;
	elem->nbr_carac = len;
	elem->show = new;
	ft_lstadd_after(elem, c);
	return (1);
}

/*
**	Si, en parcourant la chaine on croise un % on vérifie que la chaine est
**	valide, sinon retourne 0.
** 	On crée un élément de la liste chainée à chaque noeud %
** 	On parcours la chaine jusqu'à la conversion avec ft_parser, et on setup
** 	les flags avec ce meme parser
*/

static int		ft_read_format(const char *restrict format, t_chain **chain)
{
	size_t		i;
	size_t		len;
	t_chain		*elem;

	elem = NULL;
	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (i != 0 && !(ft_show_only_parser(format, i, chain)))
				return (0);
			if (!(format = ft_parser(&format[++i], ft_create_elem(), chain)))
				return (0);
			i = 0;
		}
		else
			i++;
	}
	if (i != 0)
		if (!ft_show_only_parser(format, i, chain))
			return (0);
	return (1);
}

/*
**	La fonction ft_printf prend une chaine de caractere
**	Si elle n'arrive pas à lire via read_format renvoie -1 (erreur)
** 	Sinon, envoie l'argument à ft_handler
**	(le va_end se trouve à la fin de ft_handler)
*/

int				ft_printf(const char *restrict format, ...)
{
	t_chain		*chain;
	va_list		ap;

	va_start(ap, format);
	chain = NULL;
	if (!(ft_read_format(format, &chain)))
		return (-1);
	return (ft_handler(ap, chain));
}
