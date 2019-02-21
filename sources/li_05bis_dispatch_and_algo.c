/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_05bis_dispatch_and_algo.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 21:25:13 by fallouch          #+#    #+#             */
/*   Updated: 2019/02/21 21:25:15 by fallouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_path		*return_bfs(t_files *file, t_files *tmp)
{
	t_path			*path;

	free_file(file);
	path = tmp->path;
	free(tmp);
	return (path);
}

/*
**	Imprime toute la map jusqu'a la derniere ligne valide
*/

void		ft_print_infos(t_all *elem)
{
	t_map		*tmp;

	tmp = elem->map;
	while (elem->map != NULL)
	{
		tmp = elem->map->next;
		ft_printf("%s\n", elem->map->str);
		free(elem->map->str);
		free(elem->map);
		elem->map = tmp;
	}
}

int			diff_between_path(t_tab_path *tab, int i)
{
	int difference;

	difference = 0;
	while (tab->prev != NULL)
		tab = tab->prev;
	while (i-- > 0 && tab->next)
		tab = tab->next;
	if (tab->next)
		difference = tab->next->path_size - tab->path_size;
	else
		difference = -1;
	return (difference);
}

int			ft_nb_path(t_all elem, t_tab_path *tab, int i, int capacity)
{
	int nb_ant;

	nb_ant = elem.number_ants;
	if (diff_between_path(tab, i - 1) != -1)
		capacity = capacity + (diff_between_path(tab, i) * i);
	else
		return (i);
	if (capacity > nb_ant)
		return (i);
	else
	{
		i++;
		return (ft_nb_path(elem, tab, i, capacity));
	}
}

void		add_ant(t_ant **ant, int nb, t_path *path)
{
	t_ant		*new;
	t_ant		*tmp;

	if (!(new = malloc(sizeof(t_ant))))
		return ;
	new->nb = nb;
	new->path = path_cpy(path);
	new->tmp_path = new->path;
	new->prev = NULL;
	new->next = NULL;
	if (!*ant)
		*ant = new;
	else
	{
		tmp = *ant;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}
