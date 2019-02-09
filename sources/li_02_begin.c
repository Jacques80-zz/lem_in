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
	start->available = VISITED;
	while (j < elem.number_rooms)
	{
		if (matrice[i][j] && matrice[i][j]->available != VISITED)
			find_path(elem, matrice, matrice[i][j], path_cpy(path), tab);
		j++;
	}
}

/*
void		bfs(t_all elem, t_room ***matrice, t_room *start)
{
	int				i;
	int				j;
	t_files			*file;
	t_room			*tmp;

	file = NULL;
	add_file(&file, start);
	file->room->available = VISITED;
	while (file)
	{
		tmp = remove_file(&file);
		i = tmp->room_id;
		j = 0;
		while (j < elem.number_rooms)
		{
			if (matrice[i][j] && matrice[i][j]->available == NO_VISITED)
			{
				add_file(&file, matrice[i][j]);
				matrice[i][j]->available = VISITED;
			}
			j++;
		}
	}
}*/
