/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend_w_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:55:12 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:38:26 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	ft_number_byte_for_carac est appelé pr connaitre le nombre de byte du wchar
**	Il lit le nombre de 1 sur l'octet de poids fort pour connaitre le nb de
**	de bytes sur lequel se trouve le wchar, il renvoie ce nombre
*/

static int	ft_number_byte_for_carac(char *show, int y)
{
	int byte;

	byte = 0;
	while (show[y++] == '1')
		byte++;
	return (byte);
}

/*
**	ft_initialize_prec_on_w est eecuté à la fin de ft_prec_on_w
**	elle limite le nombre de caractere affiché dans le cadre
**	d'une str de wchar, elle modifie donc le contenu de elem->show, ainsi que
**	nbr_carac et nbr_byte dans ce meme maillon
*/

static void	ft_initialize_prec_on_w(t_chain *elem, size_t i)
{
	char	*tmp;

	tmp = elem->show;
	elem->show = ft_strsub(elem->show, 0, i * 8);
	elem->nbr_carac = i;
	elem->nbr_byte = i;
	free(tmp);
}

/*
**	ft_prec_on_w est appelé quand 'S' ou 's' cummulé à conversion 'l'
**	et que elem->prec existe
**	Si precision supérieure au nbr de byte, renvoie elem->show
**	Sinon, tant que la precision n'est pas atteinte
**	On vérifie si l'octet de poids fort nous indique un char sur plusieurs
**	bytes (cas particiulier du 128 a 255)
**	Si tel est le cas on donne la nouvelle valeur en int au wchar
**	Si le nombre de byte est superieur a la prec, on limite elem->show via
**	ft_initialize_prec_on_w qui prend le size_t i en parametre
*/

char		*ft_prec_on_w(t_chain *elem)
{
	size_t	i;
	int		carac;
	int		byte;

	i = 0;
	carac = 0;
	if (elem->prec > elem->nbr_byte)
		return (elem->show);
	while (i < elem->prec && elem->show[carac])
	{
		byte = 0;
		if (elem->show[carac] == '0' || MB_CUR_MAX == 1)
			byte++;
		else if (elem->show[carac] == '1')
			byte = ft_number_byte_for_carac(elem->show, carac);
		i += byte;
		carac = i * 8;
	}
	if (i > elem->prec)
		i -= byte;
	ft_initialize_prec_on_w(elem, i);
	return (elem->show);
}
