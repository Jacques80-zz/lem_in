#include "../includes/lem_in.h"

int				is_not_in_path(t_path *path, t_room *room)
{
	while (path)
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

void			free_path(t_path *path)
{
	t_path 		*tmp;

	while (path)
	{
		tmp = path->next;
		free(path);
		path = tmp;
	}
}

void			free_tab_path(t_tab_path *tab)
{
	t_tab_path		*tmp;

	while (tab)
	{
		tmp = tab->next;
		free_path(tab->path);
		free(tab);
		tab = tmp;
	}
}