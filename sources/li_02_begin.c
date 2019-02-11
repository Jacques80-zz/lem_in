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

void		add_files(t_files **files, t_room *room, t_path *path)
{
	t_files			*new;
	t_files			*tmp;

	tmp = *files;
	if (!(new = malloc(sizeof(t_files))))
		return ;
	add_path(&path, room);
	new->path = path;
	new->room = room;
	new->next = NULL;
	if (!*files)
		*files = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_files			*pop_file(t_files **file)
{
	t_files		*tmp;

	tmp = *file;
	if (!*file)
		return (NULL);
	*file = (*file)->next;
	return (tmp);
}

void			add_path(t_path **path, t_room *room)
{
	t_path			*tmp;
	t_path			*new;

	if (!(new = malloc(sizeof(t_path))))
		return ;
	new->room = room;
	new->next = NULL;
	if (!*path)
		*path = new;
	else
	{
		tmp = *path;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		break_start_end(t_all elem, t_room ***matrice)
{
	int			i;
	int			j;

	i = elem.end_id;
	j = 0;
	while (j < elem.number_rooms)
		matrice[i][j++] = NULL;
	i = 0;
	j = elem.start_id;
	while (i < elem.number_rooms)
		matrice[i++][j] = NULL;
}

t_path		*path_cpy(t_path *path)
{
	t_path		*new;

	new = NULL;
	while (path)
	{
		add_path(&new, path->room);
		path = path->next;
	}
	return (new);
}

int			is_not_in(t_path *path, t_room *room)
{
	while (path)
	{
		if (path->room == room && room->status != END && room->status != START)
			return (0);
		path = path->next;
	}
	return (1);
}

int			compare_path(t_path *path1, t_path *path2)
{
	while (path1)
	{
		if (!is_not_in(path2, path1->room))
			return (0);
		path1 = path1->next;
	}
	return (1);
}

void		add_path_to_tab(t_tab_path **tab, t_path *path)
{
	t_tab_path			*new;

	if (!(new = malloc(sizeof(t_tab_path))))
		return ;
	new->path = path;
	new->next = *tab;
	*tab = new;
}

int		compare_tab_path(t_tab_path **tab, int len)
{
	int				i;
	int				j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (!compare_path(tab[i]->path, tab[j]->path))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	print_tab_of_path(t_tab_path **tab, int len)
{
	int			i;

	i = 0;
	while (i < len)
	{
		print_path(tab[i]->path);
		i++;
	}
}

int		old_bruteforce(t_all elem, t_tab_path *tab, t_room ***matrice)
{
	t_tab_path		**tab_bf;
	int				limit;

	limit = ft_limited_factor(&elem, matrice);
	tab_bf = malloc(sizeof(t_tab_path) * 2);
	tab_bf[0] = tab;
	while (tab_bf[0])
	{
		tab_bf[1] = tab_bf[0]->next;
		while (tab_bf[1])
		{
			if (compare_tab_path(tab_bf, 2))
			{
				ft_printf("YYOUPPPI!!!!\n");
				print_tab_of_path(tab_bf, 2);
				ft_printf("_____________FIN_____________\n");
				return (1);
			}
			tab_bf[1] = tab_bf[1]->next;
		}
		tab_bf[0] = tab_bf[0]->next;
	}
	return (0);
}

t_tab_path	**from_list_to_tab(t_tab_path *tab, int *len_tab)
{
	int			i;
	int			len;
	t_tab_path	*tmp;
	t_tab_path	**new;

	tmp = tab;
	len = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	new = malloc(sizeof(t_tab_path) * (len + 1));
	i = 0;
	while (i < len)
	{
		new[i++] = tab;
		tab = tab->next;
	}
	*len_tab = len + 1;
	new[i] = NULL;
	return (new);
}

int		ft_bruteforce(t_all elem, t_tab_path *path_tab, t_room ***matrice)
{
	int			limit;
	int			i;
	int			len;
	int			tmp_i;
	t_tab_path	*tmp;
	t_tab_path	**tab_bf;
	t_tab_path	**tab;

	i = 0;
	tmp = path_tab;
	limit = ft_limited_factor(&elem, matrice);
	if (!(tab_bf = malloc(sizeof(t_tab_path*) * limit)))
		return (0);
	tab = from_list_to_tab(path_tab, &len);
	while (i < limit)
	{
		tab_bf[i] = tab[i];
		i++;
	}
	while (tab_bf[0])
	{
		if (compare_tab_path(tab_bf, limit))
			return (1);
	}
	return (0);
}

void		search_path(t_all elem, t_room ***matrice, t_room *start,  t_tab_path **tab)
{
	int				i;
	int				j;
	t_files			*file;
	t_files			*tmp;

	add_files(&file, start, NULL);
	break_start_end(elem, matrice);
	while (file)
	{
		tmp = pop_file(&file);
		i = tmp->room->room_id;
		j = 0;
		if (tmp->room->status == END)
		{
			print_path(tmp->path);
			add_path_to_tab(tab, tmp->path);
			if (old_bruteforce(elem, *tab, matrice))
				return ;
		}
		while (j < elem.number_rooms)
		{
			if (matrice[i][j] && matrice[i][j]->weight >= tmp->room->weight && is_not_in(tmp->path, matrice[i][j]))
				add_files(&file, matrice[i][j], path_cpy(tmp->path));
			j++;
		}
	}
}
