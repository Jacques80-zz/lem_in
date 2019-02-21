/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_05_dispatch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:32:01 by jdouniol          #+#    #+#             */
/*   Updated: 2019/02/19 19:36:29 by fallouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		diff_between_path(t_tab_path *tab, int i)
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

int		ft_nb_path(t_all elem, t_tab_path *tab, int i, int capacity)
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

void	add_ant(t_ant **ant, int nb, t_path *path)
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

void	remove_ant(t_ant **ant)
{
	t_ant		*tmp;
	t_ant		*tmp_ant;

	while (*ant && (*ant)->path->room->status == END)
	{
		tmp = (*ant)->next;
		free_path((*ant)->tmp_path);
		free(*ant);
		*ant = tmp;
		if (tmp)
			tmp->prev = NULL;
	}
	tmp_ant = *ant;
	while (tmp_ant && (tmp = tmp_ant->next) + 1)
	{
		if (tmp_ant->path->room->status == END)
		{
			tmp_ant->prev->next = tmp;
			if (tmp)
				tmp->prev = tmp_ant->prev;
			free_path(tmp_ant->tmp_path);
			free(tmp_ant);
		}
		tmp_ant = tmp;
	}
}

void	move_ant(t_ant **ptr_ant)
{
	t_ant		*ant;

	ant = *ptr_ant;
	while (ant)
	{
		ant->path = ant->path->next;
		ft_printf("L%d-%s", ant->nb, ant->path->room->name_room);
		ant->next ? ft_putchar(' ') : ft_putchar('\n');
		ant = ant->next;
	}
	remove_ant(ptr_ant);
}

/*
**	Imprime toute la map jusqu'a la derniere ligne valide
*/

void	ft_print_infos(t_all *elem)
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

void	ft_dispatch_short(t_all elem, t_path *path)
{
	t_ant		*ant;

	ant = NULL;
	ft_putchar('\n');
	while (elem.number_ants)
	{
		add_ant(&ant, elem.number_ants--, path);
		move_ant(&ant);
	}
	while (ant)
		move_ant(&ant);
}

void	ft_dispatch(t_all elem, t_tab_path *tab)
{
	t_ant		*ant;
	t_tab_path	*tmp;
	int			nb;
	int			ret;

	ant = NULL;
	if (path_size(elem.shortest_path) - 2 > elem.number_ants)
		return (ft_dispatch_short(elem, elem.shortest_path));
	ft_putchar('\n');
	while (elem.number_ants)
	{
		tmp = tab;
		nb = 1;
		while (tmp && elem.number_ants)
		{
			ret = ft_nb_path(elem, tab, 1, 0);
			if (nb <= ret)
				add_ant(&ant, elem.number_ants--, tmp->path);
			tmp = tmp->next;
			nb++;
		}
		move_ant(&ant);
	}
	while (ant)
		move_ant(&ant);
}
