#include "../includes/lem_in.h"

t_room		***ft_init_matrice(int number_rooms)
{
	t_room		***matrice;

	if (!(matrice = (t_room ***)malloc(sizeof(t_room**) * (number_rooms + 1))))
		return (NULL);
	int i;
	int j;
	i = 0;
	while (i < number_rooms)
	{
		if (!(matrice[i] = malloc(sizeof(t_room*) * (number_rooms))))
			return (NULL);
		j = 0;
		while(j < number_rooms)
		{
			matrice[i][j] = NULL;
			j++;
		}
		i++;
	}
	matrice[i] = NULL;
	return (matrice);
}

void		ft_set_matrice(t_room **tmp, t_room **cur, t_room ***matrice)
{
	int id_first_room;
	int id_second_room;

	id_first_room = (*tmp)->room_id;
	id_second_room = (*cur)->room_id;
	matrice[id_first_room][id_second_room] = *cur;
	matrice[id_second_room][id_first_room] = *tmp;
}

t_room		*ft_init_start(t_all *elem)
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

t_room		*ft_init_end(t_all *elem)
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

void		ft_find_room(t_room **tmp, char *room)
{
	while (*tmp)
	{
		if (ft_strcmp((*tmp)->name_room, room) == 0)
			break ;
		(*tmp) = (*tmp)->next;
	}
}