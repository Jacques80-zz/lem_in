#include "../includes/lem_in.h"

/*
 **	Est appellee a chaque ligne valide
 **	si le malloc echoue, on utilise ft_error
 **	cas si 1ere ligne
 **	cas pour toutes les lignes suivantes 
 */

void	ft_save_map(t_all *elem, char *line)
{
	t_map	*new;
	t_map	*last;

	ft_error(!(new = malloc(sizeof(t_map))));
	ft_error(!(new->str = ft_strdup(line)));
	new->next = NULL;
	if (elem->map == NULL)
	{
		elem->map = new;
		return ;
	}
	last = elem->map;
	while (last->next)
	{
		last = last->next;
	}
	last->next = new;
}

void			push_file(t_files **files, t_room *room, t_path *path)
{
	t_files		*new;
	t_files		*tmp;

	if (!(new = malloc(sizeof(t_files))))
		return ;
	new->room = room;
	add_path(&path, room);
	new->path = path;
	new->next = NULL;
	if (!*files)
		*files = new;
	else
	{
		tmp = *files;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_files			*pop_file(t_files **file)
{
	t_files		*tmp;

	tmp = *file;
	(*file) = (*file)->next;
	return (tmp);
}

void			add_path_to_tab(t_tab_path **tab, t_path *path)
{
	t_tab_path				*new;
	t_tab_path				*tmp;

	if (!(new = malloc(sizeof(t_tab_path))))
		return ;
	new->path = path;
	new->next = NULL;
	if (!*tab)
		*tab = new;
	else
	{
		tmp = *tab;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void			free_file(t_files *file)
{
	t_files		*tmp;

	while (file)
	{
		tmp = file->next;
		free_path(file->path);
		free(file);
		file = tmp;
	}
}
