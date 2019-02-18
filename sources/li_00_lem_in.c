/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_00_lem_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:30:15 by jdouniol          #+#    #+#             */
/*   Updated: 2019/02/18 05:30:18 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
# include <stdarg.h>


/*PENSER A SUPPRIMER ELEM->MAP*/

/*
 **	Le main quoi, d'abord les cas d erreur de ft_read, puis on cherche
 **	si un chemin est possible, si oui, on active le dispatch, si non
 **	on free le tout avant de quitter
 */

int		main(int ac, char **av)
{
	t_all		elem;
	t_tab_path	*tab;

	(void)av;
	(void)ac;
	tab = NULL;
	if (ft_read(&elem) == FAIL)
	{
		ft_free_all(&elem);
		ft_printf("Error\n");
		return (EXIT_FAILURE);
	}
	else // TODO kick else et mettre check error.
	{
		ft_print_infos(&elem);
		elem.matrice_flow = create_matrice_flow(elem); // verifier ici presence de start et end
		ft_printf("start_id : %d, end_id : %d", elem.start_id, elem.end_id);
		tab = edmond_karp(&elem, elem.matrice, elem.matrice_flow, ft_init_start(&elem)); // mettre check error a la suite de edmond karp, verifier elem.shortest_path pour savoir si chemin existe. 

//		print_path(elem.shortest_path);
//		ft_putendl("=============FIN============");
		ft_dispatch(elem, tab);
		/*
		**
		*/

		free_path(elem.shortest_path);
		ft_free_matrice(elem.matrice);
		ft_free_matrice_flow(elem.matrice_flow);
		free_tab_path(tab);
		free_room(elem.room);
	}
	//exit(1);
}
