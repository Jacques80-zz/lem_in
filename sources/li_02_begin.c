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

/*void		empile(t_path **path, t_room *room)
{
	t_path		*new;
	t_path		*tmp;

	if (!(new = malloc(sizeof(t_path))))
		return ;
	new->room = room;
	new->next = NULL;
	new->prev = NULL;
	if (!path)
		*path = new;
	else
	{
		tmp = *path;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}*/

t_path			*path_cpy(t_path *path)
{
	t_path			*new;

	new = NULL;
	while (path)
	{
		empile(&new, path->room);
		path = path->next;
	}
	return (new);
}

void		add_path(t_tab_path **tab, t_path *path)
{
	t_tab_path			*new;
	t_tab_path			*tmp;

	tmp = *tab;
	if (!(new = malloc(sizeof(t_tab_path))))
		return ;
	new->next = NULL;
	new->path = path;
	if (!*tab)
		*tab = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int			G = 0;

/*void		find_path(t_all elem, t_room ***matrice, t_room *start, t_path *path, t_tab_path **tab)
{
	int			i;
	int			j;
	t_room		*tmp;

	i = start->room_id;
	j = 0;
	empile(&path, start);
	if (start->status == END)
	{
		ft_printf("G = %d\n", G);
		add_path(tab, path);
//		ft_free_matrice(matrice);
		return ;
	}
	while (j < elem.number_rooms)
	{
		G++;
		if (matrice[i][j] && matrice[i][j]->weight >= start->weight)
		{
			tmp = matrice[i][j];
			matrice[i][j] = NULL;
			matrice[j][i] = NULL;
//			find_path(elem, matrice_cpy(elem, matrice), tmp, path_cpy(path), tab);
			find_path(elem, matrice, tmp, path_cpy(path), tab);
			matrice[i][j] = tmp;
			matrice[j][i] = start;
		}
		j++;
	}
//	ft_free_matrice(matrice);
	return ;
}*/



void		find_path(t_all elem, t_room ***matrice, t_room *start, t_path *path, t_tab_path **tab)
{
	int			i;
	int			j;

	i = start->room_id;
	j = 0;
	empile(&path, start);
	if (start->status == END)
	{
		add_path(tab, path);
		return ;
	}
	while (j < elem.number_rooms)
	{
		if (matrice[i][j] && matrice[i][j]->available == NO_VISITED && matrice[i][j]->weight >= start->weight)
		{
			start->available = VISITED;
			find_path(elem, matrice, matrice[i][j], path_cpy(path), tab);
			start->available = NO_VISITED;
		}
		j++;
	}
}
