/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 03:30:46 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:29:00 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Parcourt la liste lst en appliquant à chaque maillon la fonction f et cree
**	une nouvelle liste “fraiche” avec malloc(3) resultant des applications
**	successives. Si une allocation echoue, la fonction renvoie NULL.
*/

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*current;
	t_list	*previous;
	t_list	*begin_list;

	begin_list = NULL;
	if (lst && f)
	{
		while (lst)
		{
			current = f(lst);
			current = ft_lstnew(current->content, current->content_size);
			if (begin_list)
				ft_lstaddafter(&previous, &current);
			else
				begin_list = current;
			previous = current;
			lst = lst->next;
		}
	}
	return (begin_list);
}
