/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 03:27:35 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:28:47 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Prend en parametre l’adresse d’un pointeur sur un maillon et libere la
**	memoire du contenu de ce maillon avec la fonction del passee en parametre
**	puis libere la memoire du maillon en lui meme avec free(3). La memoire du
**	champ next ne doit en aucun cas être liberee. Pour terminer, le pointeur
**	sur le maillon maintenant libere doit etre mis a NULL (de maniere similaire
**	à la fonction ft_memdel).
*/

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (alst)
	{
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = NULL;
	}
}
