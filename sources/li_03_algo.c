#include "../includes/lem_in.h"

void			put_flow_in_matrice( int **matrice_flow, t_path *path)
{
	int			i;
	int			j;

	while (path->room->status != END)
	{
		i = path->room->room_id;
		j = path->next->room->room_id;
		matrice_flow[i][j]++;
		path = path->next;
	}
}

void			delete_bad_link(t_all elem, int **matrice_flow)
{
	int			i;
	int			j;

	i = 0;
	while (i < elem.number_rooms)
	{
		j = 0;
		while (j < elem.number_rooms)
		{
			if (matrice_flow[i][j] && matrice_flow[j][i])
			{
				matrice_flow[i][j] = 0;
				matrice_flow[j][i] = 0;
			}
			j++;
		}
		i++;
	}
}

t_path			*bfs(t_all elem, t_room ***matrice, int **matrice_flow, t_room *start, int bfs)
{
	int				i;
	int				j;
	t_files			*file;
	t_files			*tmp;
	t_path 			*path;

	file = NULL;
	push_file(&file, start, NULL);
	while (file)
	{
		tmp = pop_file(&file);
		i = tmp->room->room_id;
		j = 0;
		if (tmp->room->status == END)
		{
			free_file(file);
			path = tmp->path;
			free(tmp);
			return (path);
		}
		while (j < elem.number_rooms)
		{
			if (matrice[i][j] && matrice_flow[i][j] != 1 && matrice[i][j]->bfs != bfs)
			{
				matrice[i][j]->bfs = bfs;
				push_file(&file, matrice[i][j], path_cpy(tmp->path));
			}
			j++;
		}
		free_path(tmp->path);
		free(tmp);
	}
	return (NULL);
}

t_tab_path		*return_tab_path(t_all elem, t_room ***matrice, int **matrice_flow, t_room *start)
{
	t_files				*file;
	t_files				*tmp;
	t_tab_path			*tab;
	int					i;
	int					j;

	file = NULL;
	push_file(&file, start, NULL);
	tab = NULL;
	while (file)
	{
		tmp = pop_file(&file);
		i = tmp->room->room_id;
		j = 0;
		if (tmp->room->status == END)
			add_path_to_tab(&tab, path_cpy(tmp->path));
		else
			while (j < elem.number_rooms)
			{
				if (matrice_flow[i][j])
				{
					matrice_flow[i][j] = 0;
					push_file(&file, matrice[i][j], path_cpy(tmp->path));
				}
				j++;
			}
		free_path(tmp->path);
		free(tmp);
	}
	return (tab);
}

t_tab_path			*edmond_karp(t_all *elem, t_room ***matrice, int **matrice_flow, t_room *start)
{
	t_tab_path	*tab;
	t_path		*path;
	int			bfs_nb;

	bfs_nb = 0;
	while ((path = bfs(*elem, matrice, matrice_flow, start, bfs_nb++)))
	{
		put_flow_in_matrice(matrice_flow, path);
		delete_bad_link(*elem, matrice_flow);
		if (elem->shortest_path == NULL)
			elem->shortest_path = path;
		else
			free_path(path);
	}
	tab = return_tab_path(*elem, matrice, matrice_flow, start);
	print_tab_path(tab);
	return (tab);
}
