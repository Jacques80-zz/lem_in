#include "../includes/lem_in.h"

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

void		move_ant(t_ant *ant)
{
	while (ant)
	{
		ant->path = ant->path->next;
		ft_printf("L%d-%s", ant->nb, ant->path->room->name_room);
		ant->next ? ft_putchar(' ') : ft_putchar('\n');
		ant = ant->next;
	}
}

void		remove_ant(t_ant **ant)
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
	while (tmp_ant)
	{
		tmp = tmp_ant->next;
		if (tmp_ant->path->room->status == END)
		{
			tmp_ant->prev->next = tmp;
			if (tmp)
				tmp->prev = tmp_ant->prev;
			free_path(tmp_ant->path);
			free(tmp_ant);
		}
		tmp_ant = tmp;
	}
}

void		ft_dispatch(t_all elem, t_tab_path *tab)
{
	t_ant		*ant;
	t_tab_path	*tmp;
	int			n;
	int			i;

	ant = NULL;
	n = 1;
	i = 0;
	while (n <= elem.number_ants)
	{
		tmp = tab;
		while (tmp && n <= elem.number_ants)
		{
			add_ant(&ant, n++, tmp->path);
			tmp = tmp->next;
		}
		move_ant(ant);
		remove_ant(&ant);
		i++;
	}
	while (ant)
	{
		move_ant(ant);
		remove_ant(&ant);
		i++;
	}
	ft_printf("number lines: %d\n", i);
}