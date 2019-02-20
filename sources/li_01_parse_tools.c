/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_01_parse_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:30:46 by jdouniol          #+#    #+#             */
/*   Updated: 2019/02/18 05:30:49 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	ft_status_update permet de mettre le status des rooms start et end
**	il met ensuite NO_VISITED qui signifie que l algo n est pas encore parcouru
*/

void		ft_status_update(t_all *elem, t_room *tmp)
{
	tmp->status = NOT;
	if (elem->next_is_start == 1)
	{
		tmp->status = START;
		elem->start_id = tmp->room_id;
		elem->next_is_start = 0;
	}
	else if (elem->next_is_end == 1)
	{
		tmp->status = END;
		elem->end_id = tmp->room_id;
		elem->next_is_end = 0;
	}
	tmp->available = NO_VISITED;
	if (elem->room == NULL)
	{
		elem->room = tmp;
		elem->cur = tmp;
	}
	else
	{
		elem->cur->next = tmp;
		elem->cur = tmp;
	}
}

int 		check_room(t_room *room, char **tab)
{
	int 		x;
	int 		y;

	x = ft_atol(tab[1]);
	y = ft_atol(tab[2]);
	while (room)
	{
		if (room->coord_x_room == x
			|| room->coord_y_room == y
			|| !ft_strcmp(room->name_room, tab[0]))
			return (0);
		room = room->next;
	}
	return (1);
}

/*
**	ft_room est appele lorsque la ligne contient 3 champs separes par un
** 	ou plusieurs espaces
**	si tab_coor de 1 et 2 n 'est pas un int (ferme d un \0) erreur
**	On alloue la zone memoire necessaire a un tableau de room ici tmp
**	avec atoi on sette les coordonnees x et y de la piece
**	avec strcpy on sette le nom de la piece
**	on initialise le reste des infos utiles a 0 (nb ant) ou a null
**	si on attend apres start ou end on changera l etat avec ft_status_update
**	si ni start ni end, l etat est NOT et par defaut available est NO_VISITED
*/

int				ft_room(t_all *elem, char **tab_coor)
{
	int		i;
	int		j;
	t_room	*tmp;
	int		room_id;

	room_id = elem->number_rooms;
	i = 0;
	while (tab_coor[++i] && i < 3)
		if (ft_check_nb(tab_coor[i], &j) == ERROR)
			return (ERROR);
	if (!(tmp = (t_room *)ft_memalloc(sizeof(t_room))))
		return (ERROR);
	tmp->coord_x_room = ft_atoi(tab_coor[1]);
	tmp->coord_y_room = ft_atoi(tab_coor[2]);
	if (tab_coor[0][0] == 'L' || !check_room(elem->room, tab_coor))
	{
		free(tmp);
		return (ERROR);
	}
	elem->number_rooms = elem->number_rooms + 1;
	tmp->room_id = room_id;
	tmp->available = NO_VISITED;
	tmp->name_room = ft_strdup(tab_coor[0]);
	tmp->tab = NULL;
	tmp->next = NULL;
	tmp->bfs = -1;
	ft_status_update(elem, tmp);
	return (SUCCESS);
}


/*
**	Si nous sommes la c est que la ligne n est ni un commentaire
**	ni une instruction, ni un nombre de fourmies
**	On commence par verifier s il s agit d un pipe si oui on envoie la ligne
**	a ft_tube
**	avec strsplit et ' ' on separe chaque str bornee par un espace
**	si il y a 3 champs, on utilise ft_room avec ce tableau de char
**	on free ce tableau de char cree pour l occasion  
*/

int		ft_one_line_tube_or_room(t_all *elem, char *line)
{
	char	**tab;
	int		i;
	int		ret;

	i = 0;
	if (ft_strchr(line, '-') != NULL)
		return (ft_tube(elem, line));
	if (!(tab = ft_strsplit(line, ' ')))
		return (ERROR);
	while (tab[++i]);
	if (i == 3)
	{
		ret = ft_room(elem, tab);
	}
	else
		ret = ERROR;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (ret);
}

/*
**	ft_get_instructions est appelee a chaque ligne lue par ft_read
**	Elle retourne ERROR si la ligne lue est non valide
**	Si les fourmies n'ont pas encore ete settees => ft_check_nb_ants
**	Si elle lit start, set next_is_start a 1
**	Sinon si elle lit end, set next_is_start a 1
**	sinon si elle lit un # au premier caractere la ligne est ignoree
**	Si rien de tout envoie la ligne a ft_one_line_tube_or_room
*/

int		ft_get_instructions(t_all *elem, char *line)
{
	static int	i = 0;

	if (line == NULL || line[0] == '\0')
		return (ERROR);
	else if (i == 0)
		return (ft_check_nb_ants(elem, line, &i));
	else if (ft_strcmp(line, "##start") == 0)//&& a->check.start == 0) //limiter a ##start\n ? // est ce juste avec plusieurs start?
	{
		elem->next_is_start = 1;
		return (SUCCESS);
	}
	else if (ft_strcmp(line, "##end") == 0)//&& a->check.end == 0) //limiter a ##end\n ?  // est ce juste avec plusieurs end?
	{
		elem->next_is_end = 1;
		return (SUCCESS);
	}
	else if (line[0] == '#')
		return (SUCCESS);
	else
		return (ft_one_line_tube_or_room(elem, line));
	return (SUCCESS);
}
