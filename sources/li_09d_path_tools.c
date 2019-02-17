#include "../includes/lem_in.h"

int				is_not_in_path(t_path *path, t_room *room)
{
	if (room->status == START || room->status == END)
		return (1);
	while (path->next)
	{
		if (path->room == room)
			return (0);
		path = path->next;
	}
	return (1);
}

t_path			*path_cpy(t_path *path)
{
	t_path			*new;

	new = NULL;
	while (path)
	{
		add_path(&new, path->room);
		path = path->next;
	}
	return (new);
}

void			add_path(t_path **path, t_room *room)
{
	t_path		*new;
	t_path		*tmp;

	if (!(new = malloc(sizeof(t_path))))
		return ;
	new->room = room;
	new->next = NULL;
	if (!*path)
		*path = new;
	else
	{
		tmp = *path;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}

}

int		path_size(t_path *path)
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

int 			compare_path(t_path *path1, t_path *path2)
{
	while (path1)
	{
		if (!is_not_in_path(path2, path1->room))
			return (0);
		path1 = path1->next;
	}
	return (1);
}