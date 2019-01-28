/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:08:45 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:38:01 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	ft_write_before_space est appliqué si la largeur est plus grande que strlen
**	de elem->show et que !=flag zero, dans ce cas, on met des espace puis
**	puis elem->show
*/

static char		*ft_write_before_space(char *new, t_chain *elem)
{
	size_t i;
	size_t y;

	y = 0;
	i = 0;
	while (i < (elem->width - ft_strlen(elem->show)))
		new[i++] = ' ';
	while (i < elem->width)
		new[i++] = elem->show[y++];
	free(elem->show);
	return (new);
}

/*
**	ft_write_before_zero est appliqué si la largeur est plus grande que strlen
**	de elem->show et que le flag zero est setté, dans ce cas, on met le prefixe
**	puis des 0 puis le nombre de elem->show
*/

static char		*ft_write_before_zero(char *new, t_chain *elem)
{
	char *tmp;
	long i;
	long y;

	y = 0;
	i = 0;
	tmp = ft_start_digit(elem->show, elem);
	while (i < tmp - elem->show)
		new[i++] = elem->show[y++];
	while (i < (elem->width - ft_strlen(elem->show) + tmp - elem->show))
		new[i++] = '0';
	while ((size_t)i < elem->width)
		new[i++] = elem->show[y++];
	free(elem->show);
	return (new);
}

/*
**	ft_write_after est appliqué si la largeur est plus grande que strlen de
**	elem->show et que le flag left est setté
*/

static char		*ft_write_after(char *new, t_chain *elem)
{
	size_t i;
	size_t y;

	y = 0;
	i = 0;
	while (i < (ft_strlen(elem->show)))
		new[i++] = elem->show[y++];
	while (i < elem->width)
		new[i++] = ' ';
	free(elem->show);
	return (new);
}

/*
**	ft_width_w_char est applique si 'c' & 'l' ou 's' &'l' ou 'S' ou 'C'
**	IL renvoie une nouvelle chaine de caracteres apres avoir free elem->show
**	tant que !=flag->left et que width < elem->nbr_carac on ajoute des ' '
**	puis new = elem->show
**	puis si flag->left tant que width < len on ajoute des ' '
**	On free elem->show et on renvoie new
*/

static char		*ft_width_w_char(t_chain *elem, t_flag *flag)
{
	size_t	len;
	char	*new;
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	len = elem->width + ft_strlen(elem->show) - elem->nbr_carac;
	if (!(new = ft_strnew(len)))
		return (NULL);
	while (!flag->left && i < (elem->width - elem->nbr_carac))
		new[i++] = ' ';
	while (elem->show[y])
		new[i++] = elem->show[y++];
	while (flag->left && i < len)
		new[i++] = ' ';
	elem->nbr_carac = elem->width;
	free(elem->show);
	return (new);
}

/*
**	ft_width est appele a la fin de int_modifier et str_modifier
**	si ft_is_w_char on applique ft_width_w_char
**	Si le flag->left est setté on applique ft_write_after
**	Sinon, si flag->zero on applique ft_write_before_zero
**	Si !=flag->zero on applique ft_write_before_space
**	On free new et on retourne elem->show
*/

char			*ft_width(t_chain *elem, t_flag *flag)
{
	char	*new;

	if (ft_is_w_char(elem))
		return (ft_width_w_char(elem, flag));
	if (!(new = ft_strnew(elem->width)))
		return (elem->show);
	if (flag->left)
		return (ft_write_after(new, elem));
	else
	{
		if (flag->zero)
		{
			return (ft_write_before_zero(new, elem));
		}
		else
			return (ft_write_before_space(new, elem));
	}
	free(new);
	return (elem->show);
}
