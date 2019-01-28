/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listmerge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:44:52 by jdouniol          #+#    #+#             */
/*   Updated: 2018/10/30 13:44:54 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_listmerge(t_list **begin_list1, t_list *begin_list2)
{
	t_list	*curseur;

	if (begin_list2 == 0)
		return ;
	if (*begin_list1 == 0 || begin_list1 == 0)
	{
		*begin_list1 = begin_list2;
		return ;
	}
	curseur = *begin_list1;
	while (curseur->next)
		curseur = curseur->next;
	curseur->next = begin_list2;
}
