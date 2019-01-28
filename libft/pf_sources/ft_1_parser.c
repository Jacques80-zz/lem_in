/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:06:52 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:32:24 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	Le parser s'active a chaque fois qu'on croise un noeud (%), il commence
**	par rechercher les flags (-,0,+, ,',#, *) avec ft_find_flag (cf 1bis)
**	On continue de parcourir la chaine a la recherche des autres flags possible
**	Dans l'ordre largeur (width), precision, longueur (lenght) puis conversion
**  de type (hh, h, ll, l, L, j, z)
*/

const char	*ft_parser(const char *format, t_chain *elem, t_chain **chain)
{
	const char	*tmp;
	int			y;

	if (!elem)
		return (NULL);
	y = 0;
	while (format && !elem->conv)
	{
		if (ft_find_flag(*format, elem))
			format++;
		else if (ft_isdigit(*format) && *format != '0')
			format = ft_find_width(&format[y], elem);
		else if (*format == '.')
			format = &format[(ft_find_precision(format, elem) - format)];
		else if ((tmp = ft_find_length(format, elem)))
			format = &format[tmp - format];
		else if (ft_is_conv(*format, elem))
		{
			ft_lstadd_after(elem, chain);
			return (++format);
		}
		else
			break ;
	}
	return (format);
}
