/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:54:44 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:37:43 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	ft_lstfree free les contenus du maillon envoyé en argument et de tous les
**	suivants
*/

t_chain		*ft_lstfree(t_chain *current)
{
	t_chain *tmp;
	t_chain	*next;

	tmp = current;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->flag)
			free(tmp->flag);
		if (tmp->show)
			free(tmp->show);
		tmp->next = NULL;
		free(tmp);
		tmp = next;
	}
	return (NULL);
}

/*
**	ft_percent_handler si, lors d'un noeud le premier element est un %
**	(autremment dit si on a %% dans le format), met % en elem->show[0]
**	et envoie a ft_str_modifier
*/

int			ft_percent_handler(t_chain *elem, va_list ap)
{
	(void)ap;
	if (!(elem->show = ft_strnew(1)))
		return (-1);
	elem->show[0] = '%';
	return (ft_str_modifier(elem, elem->flag));
}

/*
**	ft_w_error prend en parametre trois maillons de la chaine
**	previous setté a null par ft_show_error, current et elem
**	Le but est de free tous les maillons dans tous les cas de
**	figure possible
*/

static void	ft_w_error(t_chain *previous, t_chain *current, t_chain *elem)
{
	while (current)
	{
		if (current == elem || current->next == elem)
		{
			if (current->just_show == 1 || current == elem)
			{
				if (previous)
					previous->next = ft_lstfree(current);
				else
					current = ft_lstfree(current);
			}
			else
			{
				current->next = ft_lstfree(current->next);
			}
			break ;
		}
		if (current)
		{
			previous = current;
			current = current->next;
		}
	}
}

/*
**	ft_show_error est appliquée à la suite de ft_handler si l'application de
**	la fonction prévue renvoie -1
**	S'il s'agit d'un wchar, on free tous les maillons qui suivent et on affiche
**	avec ft_show_all du debut jusqu'au dernier maillon valide
**	Si != de wchar on applique ft_lstfree a begin et donc a tous
*/

int			ft_show_error(t_chain *elem, t_chain *begin)
{
	t_chain		*current;
	t_chain		*previous;

	previous = NULL;
	if (ft_is_w_char(elem))
	{
		if (begin == elem)
			begin = ft_lstfree(begin);
		current = begin;
		ft_w_error(previous, current, elem);
		if (begin)
			ft_show_all(begin);
	}
	if (begin)
		ft_lstfree(begin);
	return (-1);
}

/*
**	ft_error_handler est appliquée si aucune correspondance de conversion n'est
**	trouvée, dans ce cas le char de "conv" sera le 1er char de elem->show
**	puis on applique ft_str_modifier
*/

int			ft_error_handler(t_chain *elem, va_list ap)
{
	(void)ap;
	if (!(elem->show = ft_strnew(1)))
		return (-1);
	elem->show[0] = elem->conv;
	return (ft_str_modifier(elem, elem->flag));
}
