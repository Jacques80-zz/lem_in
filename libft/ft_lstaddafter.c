/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddafter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:45:09 by jdouniol          #+#    #+#             */
/*   Updated: 2018/10/30 13:45:12 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Ajoute l'element new en fin de la liste.
*/

void	ft_lstaddafter(t_list **alst, t_list **new)
{
	t_list	*tmp;

	if (alst)
	{
		tmp = (*alst)->next;
		if (new)
		{
			(*alst)->next = *new;
			(*new)->next = tmp;
		}
		else
			(*alst)->next = NULL;
	}
	else
		(*alst) = (*new);
}
