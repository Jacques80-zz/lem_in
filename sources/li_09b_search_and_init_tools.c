#include "../includes/lem_in.h"

t_room	*ft_init_start(t_all *elem)
{
	t_room *tmp;

	tmp = elem->room;
	while(tmp->status != START)
	{
		tmp = tmp->next;
	}
	elem->start_id = tmp->room_id;
	tmp->weight = 0;
	return (tmp);
}


t_room	*ft_init_end(t_all *elem)
{
	t_room *tmp;

	tmp = elem->room;
	while (tmp->status != END)
	{
		tmp = tmp->next;
	}
	elem->end_id = tmp->room_id;
	return (tmp);
}

int		ft_get_start_id(t_all *elem)
{
	t_room *tmp;

	tmp = elem->room;
	while (tmp->status != START)
	{
		tmp = tmp->next;
	}
	elem->start_id = tmp->room_id;
	tmp->weight = 0;
	return (tmp->room_id);
}

int		ft_get_end_id(t_all *elem)
{
	t_room *tmp;

	tmp = elem->room;
	while (tmp->status != END)
	{
		tmp = tmp->next;
	}
	tmp->weight = -1;
	elem->end_id = tmp->room_id;
	return (tmp->room_id);
}

t_room	*ft_get_room_by_id(t_all *elem, int room_id)
{
	t_room *tmp;

	tmp = elem->room;
	while (tmp->room_id != room_id)
	{
		tmp = tmp->next;	
	}
	return (tmp);
}

/*
**	Parcours la liste chainee jusqu'à trouver le nom exact de la piece
**	Si pas de piece identique => pointeur sur NULL (donc erreur de l'ot cote)
*/

void		ft_find_room(t_room **tmp, char *room)
{
	while (*tmp)
	{
		if (ft_strcmp((*tmp)->name_room, room) == 0)
			break ;
		(*tmp) = (*tmp)->next;
	}
}
