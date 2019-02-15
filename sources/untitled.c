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
	new->room_name = name;
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

void		ft_dispatch(t_all elem, t_tab_path *tab)
{
	t_dispatch		*dispatch;
	t_round			*round;
	int				ant;

	ant = 0;
	dispatch = NULL;
	if (path_size(elem.shortest_path) - 2 >= elem.number_ants)
	{

	}
	while (ant < elem.number_ants)
	{
		round = NULL;
	}
}