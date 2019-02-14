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

t_path			*ft_bfs_(t_all elem, t_room ***matrice, int **matrice_flow, t_room *start, int bfs)
{
	int				i;
	int				j;
	t_files			*file;
	t_files			*tmp;

	file = NULL;
	push_file(&file, start, NULL);
	while (file)
	{
		tmp = pop_file(&file);
		i = tmp->room->room_id;
		j = 0;
		if (tmp->room->status == END)
			return (tmp->path);
		while (j < elem.number_rooms)
		{
			if (matrice[i][j] && matrice_flow[i][j] != 1 && is_not_in_path(tmp->path, matrice[i][j]) && matrice[i][j]->bfs != bfs)
			{
				matrice[i][j]->bfs = bfs;
				push_file(&file, matrice[i][j], path_cpy(tmp->path));
			}
			j++;
		}
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
			add_path_to_tab(&tab, tmp->path);
		else
		{
			while (j < elem.number_rooms)
			{
				if (matrice_flow[i][j])
					push_file(&file, matrice[i][j], path_cpy(tmp->path));
				j++;
			}
		}
	}
	return (tab);
}

int				edmond_karp(t_all elem, t_room ***matrice, int **matrice_flow, t_room *start)
{
	t_tab_path	*tab;
	t_path		*path;
	int			bfs;

	bfs = 0;
	while ((path = ft_bfs_(elem, matrice, matrice_flow, start, bfs++)))
	{
		put_flow_in_matrice(matrice_flow, path);
		delete_bad_link(elem, matrice_flow);
	}
	tab = return_tab_path(elem, matrice, matrice_flow, start);
	print_tab_path(tab);
	return (1);
}