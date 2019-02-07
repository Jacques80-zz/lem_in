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

t_path		*find_path(t_room ***matrice, t_all elem, t_room *start, t_tab_path **tab)
{
	t_path		*pile;
	t_room		*tmp;
	int			i;
	int			j;

	i = start->room_id;
	j = 0;
	pile = NULL;
	if (start->status == END)
		return (new_elem_path(start));
	while (j < elem.number_rooms)
	{
		if (matrice[i][j])
		{
			tmp = matrice[i][j];
			matrice[i][j] = NULL;
			matrice[j][i] = NULL;
			pile = find_path(matrice, elem, tmp, tab);
		}
		if (pile && start->status == START)
		{
			empile(&pile, start);
			save_path(tab, pile);
			pile = NULL;
			find_path(matrice, elem, tmp, tab);
		}
		else if (pile)
		{
			empile(&pile, start);
			return (pile);
		}
		j++;
	}
	return (NULL);
}
