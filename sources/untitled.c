#include "../includes/lem_in.h"

int			path_size(t_path *path)
{
	int			i;

	i = 0;
	while (path)
	{
		i++;
		path = path->next;
	}
	return (i);
}

void		add_to_round(t_round **round, int nb, char *name)
{
	t_round 		*tmp;
	t_round 		*new;

	if (!(new = malloc(sizeof(t_round))))
		return ;
	new->nb = nb;
	new->name_room = name;
	new->next = NULL;
	tmp = *round;
	if (!*round)
		*round = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_dispatch 	*create_new_dispatch(void)
{
	t_dispatch 		*new;

	if (!(new = malloc(sizeof(t_dispatch))))
		return (NULL);
	new->round = NULL;
	new->next = NULL;
	return (new);
}

void		add_to_dispatch(t_dispatch **dispatch, int n, int nb, char *name)
{
	int				i;
	t_dispatch 		*new;
	t_dispatch 		*tmp;

	i = 1;
	if (!*dispatch)
		*dispatch = create_new_dispatch();
	tmp = *dispatch;
	while (i++ < n && tmp->next)
		tmp = tmp->next;
	if (!tmp->next)
	{
		tmp->next = create_new_dispatch();
		tmp = tmp->next;
	}
	add_to_round(&(tmp->round), nb, name);
}

void		print_dispatch(t_dispatch *dispatch)
{
	while (dispatch)
	{
		while (dispatch->round)
		{
			ft_printf("L%d-%s", dispatch->round->nb, dispatch->round->name_room);
			if (round->next)
				ft_putchar(' ');
			dispatch->round = dispatch->round->next;
		}
		dispatch = dispatch->next;
	}
}

void		ft_dispatch(t_all elem, t_tab_path *tab)
{
	t_dispatch		*dispatch;
	t_tab_path		*tmp;
	t_path 			*tmp_path;
	int				i;
	int				ant;

	ant = 0;
	i = 0;
	dispatch = NULL;
	tmp_dispatch = NULL;
	if (path_size(elem.shortest_path) - 2 >= elem.number_ants)
	{

	}
	while (ant <= elem.number_ants)
	{
		tmp = tab;
		while (tmp && ant <= elem.number_ants)
		{
			tmp_path = tmp->path;
			tmp_path = tmp_path->next;
			while (tmp_path)
			{
				add_to_dispatch(&dispatch, i, ant, tmp->path->room->name_room);
				tmp_path = tmp_path->next;
			}
			tmp = tmp->next;
			ant++;
		}
		i++;
	}
	print_dispatch(dispatch);
}