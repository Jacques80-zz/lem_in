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

void		add_files(t_files **file, t_room *room, int n)
{
	t_files		*new;
	t_files		*tmp;

	if (!(new = malloc(sizeof(t_files))))
		return ;
	new->room = room;
	new->n = n;
	new->next = NULL;
	if (!*file)
		*file = new;
	else
	{
		tmp = *file;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_room		*remove_files(t_files **file)
{
	t_room		*tmp;
	t_files		*temp;

	temp = *file;
	tmp = (*file)->room;
	*file = (*file)->next;
	free(temp);
	return (tmp);
}


void	add_to_path(t_path **path, t_room *room)
{
	t_path		*tmp;
	t_path		*new;

	if (!(new = malloc(sizeof(t_path))))
		return ;
	new->room = room;
	new->next = NULL;
	tmp = *path;
	if (!*path)
		*path = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_path		*path_copy(t_path *path)
{
	t_path			*new;

	new = NULL;
	while (path)
	{
		add_to_path(&new, path->room);
		path = path->next;
	}
	return (new);
}

void	add_path_to_tab(t_tab_path **tab, t_room *room, int n, t_path *path)
{
	int			i;
	t_tab_path	*tmp;
	t_tab_path	*new;

	i = 0;
	tmp = *tab;
	while (i < n - 1)
	{
		tmp = tmp->next;
		i++;
	}
	if (i == n && *tab)
		add_to_path(&(tmp->path), room);
	else
	{
		if (!(new = malloc(sizeof(t_tab_path))))
			return ;
		new->path = path_copy(path);
		add_to_path(&(new->path), room);
		if (*tab)
			tmp->next = new;
		else
			*tab = new;
	}
}

t_path	*return_path(t_tab_path *tab_path, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		tab_path = tab_path->next;
		i++;
	}
	if (i == n && tab_path)
		return (tab_path->path);
	return (NULL);
}

void	block_end(t_all elem, t_room ***matrice)
{
	int			i;
	int			j;

	j = 0;
	i = elem.end_id;
	while (j < elem.number_rooms)
	{
		if (matrice[i][j])
			matrice[i][j] = NULL;
		j++;
	}
}

void	find_paths(t_all elem, t_room ***matrice, t_room *start, t_tab_path **tab)
{
	t_files			*file;
	t_path			*tmp_path;
	t_room			*tmp;
	int				i;
	int				j;
	int				n;

	file = NULL;
	add_files(&file, start, 0);
	while (file)
	{
		n = file->n;
		tmp_path = return_path(*tab, n); 
		tmp = remove_files(&file);
		i = tmp->room_id;
		j = 0;
//		print_tab_path(*tab);
		while (j < elem.number_rooms)
		{
			if (matrice[i][j] && matrice[i][j]->weight >= tmp->weight)
			{
				if (matrice[i][j]->status != END)
					add_files(&file, matrice[i][j], n);
				add_path_to_tab(tab, matrice[i][j], n++, tmp_path);
			}
			j++;
		}
	}
}
