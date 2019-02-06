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

typedef struct					s_path
{
	t_room			*room;
	struct s_path	*next;
}								t_path;

typedef struct					s_tab_path
{
	
}

void		empile(t_path **pile, t_room *room)
{
	t_stack			*new;

	if (!(new = malloc(sizeof(t_path))))
		return ;
	new->room = room;
	new->next = *pile;
	*pile = new;
}

void		find_path(t_room ***matrice, t_all elem)
{
	t_path		**tab_path
}
