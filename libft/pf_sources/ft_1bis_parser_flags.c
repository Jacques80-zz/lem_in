/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:07:15 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:34:56 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	ft_find_flag met a 1 le flag correspondant dans la struct flag
** 	Dans l'ordre - justifie le printf a gauche
**	0 ajoute des 0 sur la largeur demandee si il n y a pas de data a afficher
**	+ oblige a signer le nombre affiche (sauf pour octal et hexa)
**	' ' ou space si aucun signe n'est affiche, met un espace avant le nombre
**	' ou apos ajoute le separateur entre les milliers si localeconv (3) is set
**	# indique que la valeur doit etre retournee sous une autre forme
**	attention si a, A, e, E, f, F, g, et G, ajoute un point decimal y compris
**	si rien apres la virgule
*/

int				ft_find_flag(char c, t_chain *elem)
{
	if (c == '-' || c == '0' || c == '+' || c == ' ' || c == 39 || c == '#' ||
			c == '*')
	{
		if (c == '-')
			(elem->flag)->left = 1;
		else if (c == '0')
			(elem->flag)->zero = 1;
		else if (c == '+')
			(elem->flag)->plus = 1;
		else if (c == ' ')
			(elem->flag)->blank = 1;
		else if (c == 39)
			(elem->flag)->apos = 1;
		else if (c == '#')
			(elem->flag)->hash = 1;
		return (1);
	}
	else
		return (0);
}

/*
**	ft_find_width trouve la largeur souhaitee, on la declenche a la suite du
**	noeud % si il est suivi de 1 ou plusieurs chffres, puis on renvoie
**	l'adresse de la fin de la largeur
*/

const char		*ft_find_width(const char *format, t_chain *elem)
{
	int	y;

	y = 0;
	while (ft_isdigit(format[y]))
		y++;
	elem->width = ft_atoi(format);
	return (&format[y]);
}

/*
**	ft_find_precision trouve la prec souhaitee, on la declenche a la suite du
**	'.' qui indique la prec. On set elem->give_p a 1 et elem->prec avec la
**	la valeur trouvee a la suite du point, puis on renvoie l'adresse de la fin
**	de la prec
*/

const char		*ft_find_precision(const char *format, t_chain *elem)
{
	int	y;

	y = 1;
	while (ft_isdigit(format[y]))
		y++;
	elem->give_p = 1;
	elem->prec = ft_atoi(&format[1]);
	return (&format[y]);
}

/*
**	ft_find_lenght trouve la conversion de type souhaitee, on la declenche si
**	on match avec une valeur de la structure s_len cf header
**	si tel est le cas on renvoie l'adresse de format + offset (1 ou 2)
*/

const char		*ft_find_length(const char *format, t_chain *elem)
{
	int		y;

	y = 0;
	while (g_len[y].len)
	{
		if (ft_match(format, g_len[y].len))
		{
			elem->len = g_len[y].c;
			return (&format[g_len[y].i]);
		}
		y++;
	}
	return (NULL);
}

/*
**	ft_is_conv regarde si le caractere c est uppercase si oui elem->maj = 1
**	sinon elem->maj = 0 (pour apres), puis si correspondance avec un element
**	de la structure s_conv cf header, on envoie le pointeur sur fonction
**	correspondant a elem->f. Sinon, elem->f = ft_error_handler
*/

int				ft_is_conv(char c, t_chain *elem)
{
	int		i;

	i = 0;
	elem->maj = (c >= 65 && c <= 90) ? 1 : 0;
	while (g_conv[i].conv)
	{
		if (g_conv[i].conv == c)
		{
			elem->conv = c;
			elem->f = g_conv[i].f;
			return (1);
		}
		i++;
	}
	if (c)
	{
		elem->conv = c;
		elem->f = &ft_error_handler;
		return (1);
	}
	else
		return (0);
}
