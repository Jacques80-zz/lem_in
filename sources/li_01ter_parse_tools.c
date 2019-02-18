/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_01ter_parse_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:30:57 by jdouniol          #+#    #+#             */
/*   Updated: 2019/02/18 05:31:02 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	ft_init_elem est appele au debut de ft_read
**	elle met tous les int a 0 et les tableaux (char ou room) a NULL
*/

void			ft_init_elem(t_all *elem)
{
	elem->number_ants = 0;
	elem->number_rooms = 0;
	elem->room = NULL;
	elem->matrice_init = 0;
	elem->matrice = NULL;
	elem->map = NULL;
	elem->next_is_start = 0;
	elem->next_is_end = 0;
	elem->shortest_path = NULL;
	elem->flow_max = -1;
}

/*
**	ft_read est appele au debut du lem in
**	il lit le fichier entre en parametre ligne par ligne
**	Si GNL renvoie une erreur (-1) le programme s'arrete ici (apres avoir free)
**	tant que get_instructions est valide, on enregistre les datas avec
**		ft_save_map
**	Si get_instructions lit une ligne invalide, on checke si l'ensemble de la
**	map lue ( a ce stade donc save dans elem)  permet d'aller de start a end
**	Si oui retourne ERROR (1), sinon retourne FAIL (2)
**	Si GNL = 0, on checke si la charte est resolvable
**	Si oui on retourne SUCCESS, sinon retourne FAIL
*/

int				ft_read(t_all *elem)
{
	int		i;
	char	*line;

	ft_init_elem(elem);
	i = GNL_LINE_READ;
	line = NULL;
	while (i == GNL_LINE_READ)
	{
		line = NULL;
		if ((i = get_next_line(STDIN_FILENO, &line)) == GNL_ERROR)
			return (FAIL);
		if (i == GNL_END)
		{
			free(line);
			break ;
		}
		if (ft_get_instructions(elem, line) == ERROR)
		{
			free(line);
			return (ERROR);//( Si carte reseolvable ? ERROR : FAIL); //cas ou la carte esr resolvable malgre une ligne d'erreur
		}
		ft_save_map(elem, line);
		free(line);
	}
	return (SUCCESS);//(Si carte resolvable) ? SUCCESS : FAIL); //  if path found retourne success sinon fail
}
