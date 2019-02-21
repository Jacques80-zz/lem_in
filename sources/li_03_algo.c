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
			path->room->available = POSSIBLE_PATH;
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
			}
			j++;
		}
		i++;
	}
}

t_path		*bfs(t_all elem, t_room ***matrice, int **flow, t_room *start)
{
	int				i;
	int				j;
	t_files			*file;
	t_files			*tmp;

	file = NULL;
	push_file(&file, start, NULL);
	while (file && (tmp = pop_file(&file)))
	{
		i = tmp->room->room_id;
		j = -1;
		if (tmp->room->status == END)
			return (return_bfs(file, tmp));
		while (++j < elem.number_rooms)
			if (matrice[i][j] && matrice[i][j]->available != VISITED
				&& flow[i][j] != 1 && matrice[i][j]->bfs != elem.bfs)
			{
				if (matrice[i][j]->available == POSSIBLE_PATH)
					matrice[i][j]->available = VISITED;
				matrice[i][j]->bfs = elem.bfs;
				push_file(&file, matrice[i][j], path_cpy(tmp->path));
			}
		free_bfs(tmp);
	}
	return (NULL);
}

t_tab_path	*return_tab_path(t_all elem, t_room ***mat, int **flow, t_room *s)
{
	t_files				*file;
	t_files				*tmp;
	t_tab_path			*tab;
	int					i;
	int					j;

	file = NULL;
	push_file(&file, s, NULL);
	tab = NULL;
	while (file && (tmp = pop_file(&file)))
	{
		i = tmp->room->room_id;
		j = -1;
		if (tmp->room->status == END)
			add_path_to_tab(&tab, path_cpy(tmp->path));
		else
			while (++j < elem.number_rooms)
				if (flow[i][j])
				{
					flow[i][j] = 0;
					push_file(&file, mat[i][j], path_cpy(tmp->path));
				}
		free_bfs(tmp);
	}
	return (tab);
}

t_tab_path	*edmond_karp(t_all *elem, t_room ***matrice, int **flow, t_room *s)
{
	t_tab_path	*tab;
	t_path		*path;

	if (!matrice)
		return (NULL);
	while ((path = bfs(*elem, matrice, flow, s)))
	{
		put_flow_in_matrice(flow, path);
		delete_bad_link(*elem, flow);
		if (elem->shortest_path == NULL)
			elem->shortest_path = path;
		else
			free_path(path);
		elem->bfs++;
	}
	tab = return_tab_path(*elem, matrice, flow, s);
	tab = remove_bad_path(tab);
	return (tab);
}
