/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_03_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:31:20 by jdouniol          #+#    #+#             */
/*   Updated: 2019/02/19 15:30:17 by fallouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		put_flow_in_matrice(int **matrice_flow, t_path *path)
{
	int			i;
	int			j;

	while (path->room->status != END)
	{
		if (path->room->status != START)
			path->room->available = VISITED;
		i = path->room->room_id;
		j = path->next->room->room_id;
		matrice_flow[i][j]++;
		path = path->next;
	}
}

void		delete_bad_link(t_all elem, int **matrice_flow)
{
	int			i;
	int			j;
	t_room		***matrice;

	i = 0;
	matrice = elem.matrice;
	while (i < elem.number_rooms)
	{
		j = 0;
		while (j < elem.number_rooms)
		{
			if (matrice_flow[i][j] && matrice_flow[j][i])
			{
				matrice_flow[i][j] = 0;
				matrice_flow[j][i] = 0;
				matrice[i][j]->available = NO_VISITED;
				matrice[j][i]->available = NO_VISITED;
			}
			j++;
		}
		i++;
	}
}

t_path 		*return_bfs(t_files *file, t_files *tmp)
{
	t_path			*path;

	free_file(file);
	path = tmp->path;
	free(tmp);
	return (path);
}

t_path		*bfs(t_all elem, t_room ***matrice, int **matrice_flow, t_room *start, int bfs) // TODO trop de parametres et trop de lignes, et certianes lignes trop grande
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
		j = -1;
		if (tmp->room->status == END)
			return (return_bfs(file, tmp));
		while (++j < elem.number_rooms)
			if (matrice[i][j] && matrice[i][j]->available != VISITED
				&& matrice_flow[i][j] != 1 && matrice[i][j]->bfs != bfs)
			{
				matrice[i][j]->bfs = bfs;
				push_file(&file, matrice[i][j], path_cpy(tmp->path));
			}
		free_path(tmp->path);
		free(tmp);
	}
	return (NULL);
}

t_tab_path	*return_tab_path(t_all elem, t_room ***matrice, int **matrice_flow, t_room *start)
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
				if (matrice_flow[i][j] && matrice[i][j] != VISITED)
				{
					matrice_flow[i][j] = 0;
					matrice[i][j]->available = VISITED;
					push_file(&file, matrice[i][j], path_cpy(tmp->path));
				}
				j++;
			}
		free_path(tmp->path);
		free(tmp);
	}
	return (tab);
}

int 		check_matrice_flow(t_all elem, int **matrice_flow)
{
	int 		i;
	int 		j;

	i = 0;
	while (i < elem.number_rooms)
	{
		j = 0;
		while (j < elem.number_rooms)
		{
			if (matrice_flow[i][j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_tab_path	*edmond_karp(t_all *elem, t_room ***matrice, int **matrice_flow, t_room *start)
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
	ft_printf("tab size = %d", tab_size(tab));
//	tab = remove_bad_path(tab); // TODO leak quand pas de chemin dispo
	if (check_matrice_flow(*elem, matrice_flow))
		ft_putendl("y a un flow qui reste");
	ft_printf("tab size = %d", tab_size(tab));
//	print_tab_path(tab);
	return (tab);
}
