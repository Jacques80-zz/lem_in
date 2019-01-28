/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chainfct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:52:22 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:38:33 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	Toutes les fonctions utiles pour les struct elem + flag
**	ft_init_chain_info set a 0 ou NULL chaque entree des structures
**	ft_lstadd_after ajoute un element de la liste a la suite des autres
**	ft_create_elem cree une structure chain qui contient un struct flag
**	et l'init a 0
*/

void			ft_init_chain_info(t_chain *elem, t_flag *flag)
{
	flag->left = 0;
	flag->blank = 0;
	flag->plus = 0;
	flag->zero = 0;
	flag->apos = 0;
	flag->hash = 0;
	elem->just_show = 0;
	elem->nbr_carac = 0;
	elem->width = 0;
	elem->give_p = 0;
	elem->prec = 0;
	elem->len = '\0';
	elem->maj = 0;
	elem->cnull = 1;
	elem->conv = 0;
	elem->show = NULL;
	elem->next = NULL;
}

void			ft_lstadd_after(t_chain *elem, t_chain **chain)
{
	t_chain	*tmp;

	tmp = *chain;
	if (tmp == NULL)
		*chain = elem;
	else
	{
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = elem;
	}
}

t_chain			*ft_create_elem(void)
{
	t_chain	*new;
	t_flag	*flag;

	if (!(new = malloc(sizeof(t_chain))))
		return (NULL);
	if (!(flag = malloc(sizeof(t_flag))))
	{
		free(new);
		return (NULL);
	}
	new->flag = flag;
	ft_init_chain_info(new, flag);
	return (new);
}
