/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 03:28:52 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:28:56 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Parcourt la liste lst en appliquant a chaque maillon la fonction f
*/

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst != NULL && f != NULL)
	{
		while (lst != NULL)
		{
			f(lst);
			lst = lst->next;
		}
	}
}
