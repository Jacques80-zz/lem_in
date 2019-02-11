#include "../includes/lem_in.h"

void		empile(t_path **pile, t_room *room)
{
	t_path			*new;
	t_path			*tmp;

	if (!(new = malloc(sizeof(t_path))))
		return ;
	new->room = room;
	new->next = NULL;
	if (!*pile)
		*pile = new;
	else
	{
		tmp = *pile;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
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
	t_path	*new;

	if (!(new = malloc(sizeof(t_path))))
		return (NULL);
	new->room = room;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
/*
t_path	**ft_init_tab_path(t_path *path) // cette fonction ne marche pas, je n' ai plus les yeux en face des trous, je galere un peu j arrete la... 
{
	t_tab_path	*tab_path;
	(void)path; // pour contrer l erreur de compil qui me dit unused identifier, mais on devrait peut etre appeler init tab path avec un vrai chemin en parametre

	if (!(tab_path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	tab_path.path = path;
	tab_path->next = NULL;
	tab_path->prev = NULL;
	return (tab_path);
}
*/
/*
t_path **ft_add_path_to_tab_path(t_path **tab_path, t_path *path)//, int path_id)
{
	int i;
//	t_tab_path *new;

	i = 0;
	while(tab_path[i] != NULL)
		i++;
	tab_path[i] = path;
	i++;
	tab_path[i] = NULL;
	return (tab_path);

}*/