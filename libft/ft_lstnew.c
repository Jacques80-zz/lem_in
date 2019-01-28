/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 03:01:32 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/30 03:07:51 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Alloue avec malloc(3) et retourne un maillon “frais”. Les champs content
**	et content_size du nouveau maillon sont initialises par copie des
**	parametres de la fonction. Si le parametre content est nul, le champs
**	content est initialise a NULL et le champs content_size est initialise a 0
**	quelque soit la valeur du parametre content_size. Le champ next est
**	initialise a NULL. Si l’allocation echoue, la fonction renvoie NULL.
*/

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		if (!(new->content = ft_memalloc(content_size)))
			return (NULL);
		new->content = ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	return (new);
}
