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

void		empile(t_path **pile, t_room *room)
{
	t_path			*new;

	if (!(new = malloc(sizeof(t_path))))
		return ;
	new->room = room;
	new->next = *pile;
	*pile = new;
}

t_path		*new_elem_path(t_room *room)
{
	t_path			*new;

	if (!(new = malloc(sizeof(t_path))))
		return (NULL);
	new->next = NULL;
	new->room = room;
	return (new);
}

void		print_path(t_path *path)
{
	while (path)
	{
		ft_printf("%s\n", path->room->name_room);
		path = path->next;
	}
	ft_printf("_______________________________\n");
}

void		print_tab_path(t_tab_path *tab)
{
	while (tab)
	{
		print_path(tab->path);
		tab = tab->next;
	}
}

void		save_path(t_tab_path **tab, t_path *path)
{
	t_tab_path		*new;

	if (!(new = malloc(sizeof(t_tab_path))))
		return ;
	new->path = path;
	new->next = *tab;
	*tab = new;
}

t_path		*find_path(t_room ***matrice, t_all elem, t_room *start, t_tab_path **tab)
{
	t_path		*pile;
	t_room		*tmp;
	int			i;
	int			j;

	i = start->room_id;
	j = 0;
	pile = NULL;
	if (start->status == END)
		return (new_elem_path(start));
	while (j < elem.number_rooms)
	{
		if (matrice[i][j])
		{
			tmp = matrice[i][j];
			matrice[i][j] = NULL;
			matrice[j][i] = NULL;
			pile = find_path(matrice, elem, tmp, tab);
		}
		if (pile && start->status == START)
		{
			empile(&pile, start);
			save_path(tab, pile);
			pile = NULL;
			find_path(matrice, elem, tmp, tab);
		}
		else if (pile)
		{
			empile(&pile, start);
			return (pile);
		}
		j++;
	}
	return (NULL);
}
