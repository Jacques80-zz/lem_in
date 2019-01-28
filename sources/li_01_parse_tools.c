
#include "../includes/lem_in.h"

void		ft_status_update(t_all *elem, t_room *tmp)
{
	tmp->status = NOT;
	if (elem->next_is_start == 1)
	{
		tmp->status = START;
	//	elem->check.start = 1;
		tmp->linked_to_start = 0;
		elem->next_is_start = 0;
	}
	else if (elem->next_is_end == 1)
	{
		tmp->status = END;
	//	elem->check.end = 1;
		tmp->linked_to_start = 0;
		elem->next_is_end = 0;
	}
	//tmp->weight = -1;
	tmp->available = NO_VISITED;
	if (elem->room == NULL)
	{
		elem->room = tmp;
		elem->cur = tmp;
	}
	else
	{
		elem->cur->next = tmp;
		elem->cur = tmp;
	}
}

int				ft_room(t_all *elem, char **tab_coor)
{
	int		i;
	int		j;
	t_room	*tmp;

	i = 0;
	while (tab_coor[++i] && i < 3)
		if (ft_check_nb(tab_coor[i], &j) == ERROR)
			return (ERROR);
	if (!(tmp = (t_room *)malloc(sizeof(t_room))))
		return (ERROR);
	tmp->coord_x_room = ft_atoi(tab_coor[1]);
	tmp->coord_y_room = ft_atoi(tab_coor[2]);
	if (tab_coor[0][0] == 'L')
		return (ERROR);
	tmp->name_room = ft_strnew(ft_strlen(tab_coor[0]));
	tmp->name_room = ft_strcpy(tmp->name_room, tab_coor[0]);
	tmp->number_ants_in_room = 0;
	tmp->tab = NULL;
	tmp->prev = NULL;
	tmp->next = NULL;
	ft_status_update(elem, tmp);
	return (SUCCESS);
}

int		ft_one_line_tube_or_room(t_all *elem, char *line)
{
	char	**tab;
	int		i;
	int		ret;

	i = 0;
	if (ft_strchr(line, '-') != NULL)
		return (ft_tube(elem, line));
	if (!(tab = ft_strsplit(line, ' ')))
		return (ERROR);
	while (tab[++i])
		;
	if (i == 3)
		ret = ft_room(elem, tab);
	else
		ret = ERROR;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (ret);
}

int		ft_get_instructions(t_all *elem, char *line)
{
	static int	i = 0;

	if (line == NULL || line[0] == '\0')
		return (ERROR);
	else if (i == 0)
		return (ft_check_nb_ants(elem, line, &i));
	else if (ft_strcmp(line, "##start") == 0)//&& a->check.start == 0) //limiter a ##start\n ?
	{
		elem->next_is_start = 1;
		return (SUCCESS);
	}
	else if (ft_strcmp(line, "##end") == 0 )//&& a->check.end == 0) //limiter a ##end\n ?
	{
		elem->next_is_end = 1;
		return (SUCCESS);
	}
	else if (line[0] == '#')
		return (SUCCESS);
	else
		return (ft_one_line_tube_or_room(elem, line));
	return (SUCCESS);
}
