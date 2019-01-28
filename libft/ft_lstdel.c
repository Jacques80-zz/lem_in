/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 03:26:08 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:28:43 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Prend en parametre l’adresse d’un pointeur sur un maillon et libere la
**	memoire de ce maillon et celle de tous ses successeurs l’un apres l’autre
**	avec del et free(3). Pour terminer, le pointeur sur le premier maillon
**	maintenant libere doit etre mis à NULL (de maniere similaire à la
**	fonction ft_memdel).
*/

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *ptr;

	if (alst && del)
	{
		ptr = *alst;
		while (ptr)
		{
			del(ptr->content, ptr->content_size);
			free(ptr);
			ptr = ptr->next;
		}
		(*alst) = NULL;
	}
}
