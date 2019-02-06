#include "../includes/lem_in.h"

/*
 **	Est appellee a chaque ligne valide
 **	si le malloc echoue, on utilise ft_error
 **	cas si 1ere ligne
 **	cas pour toutes les lignes suivantes 
 */

void	ft_save_map(t_all *elem, char *line)
{
	t_map	*new;
	t_map	*last;

	ft_error(!(new = malloc(sizeof(t_map))));
	ft_error(!(new->str = ft_strdup(line)));
	new->next = NULL;
	if (elem->map == NULL)
	{
		elem->map = new;
		return ;
	}
	last = elem->map;
	while (last->next)
	{
		last = last->next;
	}
	last->next = new;
}

t_room*find_n_room(t_all elem, int nb)
{
	int			i;

	i = 0;
	while (i++ < nb)
		elem.room = elem.room->next;
	return (elem.room);
}

void		empile(t_path **pile, t_room *room)
{
	t_path		*new;

	if (!(new = malloc(sizeof(t_path))))
		return ;
	new->room = room;
	new->next = *pile;
	*pile = new;
}

t_path		*new_elem_path(t_room *room)
{
	t_path*new;

	if (!(new = malloc(sizeof(t_path))))
		return (NULL);
	new->room = room;
	new->next = NULL;
	return (new);
}

void		print_path(t_path *path)
{
	while (path)
	{
		ft_printf("%s\n", path->room->name_room);
		path = path->next;
	}
}

t_path		*find_path(t_room ***matrice, t_all elem, int start, int end)
{
	t_tab_path	*tab;
	t_path		*pile;
	int			i;
	int			j;

	pile = NULL;
	tab = NULL;
	i = start;
	j = 0;
	if (start == end)
	{
		empile(&pile, find_n_room(elem, start));
		return (pile);
	}
	while (j < elem.number_rooms)
	{
		if (matrice[i][j])
		{
			matrice[i][j] = NULL;
			matrice[j][i] = NULL;
			pile = find_path(matrice, elem, j, end);
		}
		if (pile)
		{
			empile(&pile, find_n_room(elem, start));
			print_path(pile);
			return (pile);
		}
		j++;
	}
	return (NULL);
}
