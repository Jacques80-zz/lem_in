#include "../includes/lem_in.h"

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

t_tab_path	*create_new_tab(t_tab_path *tab)
{
	t_tab_path			*new;

	new = NULL;
	while (tab)
	{
		if (tab->path)
			add_path_to_tab(&new, path_cpy(tab->path));
		tab = tab->next;
	}
	return (new);
}

int			tab_size(t_tab_path *tab)
{
	int				i;

	i = 0;
	while (tab)
	{
		i++;
		tab = tab->next;
	}
	return (i);
}

t_tab_path	*remove_bad_path(t_tab_path *tab)
{
	t_tab_path		*tmp;
	t_tab_path		*tmp_tab;
	t_tab_path		*new;

	tmp_tab = tab;
	while (tab->next)
	{
		tmp = tab;
		while (tmp->next && (tmp = tmp->next))
		{
			if (tmp->path == NULL)
				continue ;
			if (!compare_path(tab->path, tmp->path))
			{

				free_path(tmp->path);
				tmp->path = NULL;
			}
		}
		tab = tab->next;
	}
	new = create_new_tab(tmp_tab);
	free_tab_path(tmp_tab);
	return (new);
}

