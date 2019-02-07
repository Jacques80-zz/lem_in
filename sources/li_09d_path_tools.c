#include "../includes/lem_in.h"

void		empile(t_path **pile, t_room *room)
{
	t_path			*new;

	if (!(new = malloc(sizeof(t_path))))
		return ;
	new->room = room;
	new->next = *pile;
	*pile = new;
}

t_path		*new_elem_path(t_room *room)
{
	t_path			*new;

	if (!(new = malloc(sizeof(t_path))))
		return (NULL);
	new->next = NULL;
	new->room = room;
	return (new);
}

void		print_path(t_path *path)
{
	while (path)
	{
		ft_printf("%s\n", path->room->name_room);
		path = path->next;
	}
	ft_printf("_______________________________\n");
}

void		print_tab_path(t_tab_path *tab)
{
	while (tab)
	{
		print_path(tab->path);
		tab = tab->next;
	}
}

void		save_path(t_tab_path **tab, t_path *path)
{
	t_tab_path		*new;

	if (!(new = malloc(sizeof(t_tab_path))))
		return ;
	new->path = path;
	new->next = *tab;
	*tab = new;
}

t_path	*ft_init_path(t_room *room)
{
	t_path	*path;

	if (!(path = (t_path *)malloc(sizeof(t_path) * 4096)))
		return (NULL);
	path->room = room;
	path->next = NULL;
	path->prev = NULL;
	return (path);
}