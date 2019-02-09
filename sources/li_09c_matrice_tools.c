#include "../includes/lem_in.h"

void	print_room(t_all elem, int nb)
{
	int			i;

	i = 0;
	while (i++ < nb)
		elem.room = elem.room->next;
	ft_printf("%-9s|", elem.room->name_room);
}

void	print_all_name(t_all elem)
{
	int			i;

	i = 0;
	ft_printf("%-10s", "");
	while (elem.room)
	{
		ft_printf("%-10s", elem.room->name_room);
		elem.room = elem.room->next;
	}
	ft_putchar('\n');
	ft_printf("%-10s", "");
	while (++i < elem.number_rooms)
		ft_printf("___________");
	ft_putchar('\n');
}


void	ft_print_matrice(t_room ***matrice, t_all *elem)
{
	int i;
	int j;

	i = 0;
	print_all_name(*elem);
	while (i < elem->number_rooms)
	{
		j = 0;
		print_room(*elem, i);
		while (j < elem->number_rooms)
		{
			if (matrice[i][j])
				ft_printf("%-10s", matrice[i][j]->name_room);
			else
				ft_printf("%-10s", "~");
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n\n\n");
}

/*
**
*/


void	ft_set_matrice(t_room **tmp, t_room **cur, t_room ***matrice)
{
	int id_first_room;
	int id_second_room;

	id_first_room = (*tmp)->room_id;
	id_second_room = (*cur)->room_id;
	matrice[id_first_room][id_second_room] = *cur;
	matrice[id_second_room][id_first_room] = *tmp;
}

/*
**
*/

t_room	***ft_init_matrice(int number_rooms)
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

void	ft_print_matrice_weight(t_room ***matrice, t_all *elem)
{
	int i;
	int j;

	i = 0;
	print_all_name(*elem);
	while (i < elem->number_rooms)
	{
		j = 0;
		print_room(*elem, i);
		while (j < elem->number_rooms)
		{
			if (matrice[i][j])
				ft_printf("%-10d", matrice[i][j]->weight);
			else
				ft_printf("%-10s", "~");
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n\n\n");
}

int 	ft_limited_factor(t_all *elem, t_room ***matrice)
{
	int i;
	int j;
	int links_to_start;
	int links_to_end;
	int k;

	i = elem->start_id;
	j = elem->end_id;
	links_to_end = 0;
	links_to_start = 0;
	k = 0;
	while (k < elem->number_rooms)
	{
		if (matrice[i][k])
			links_to_start++;
		if (matrice[j][k])
			links_to_end++;
		k++;
	}
	return (ft_min(links_to_start, links_to_end));
}

t_room		***matrice_cpy(t_all elem, t_room ***matrice)
{
	int				i;
	int				j;
	t_room			***new_matrice;

	i = 0;
	if (!(new_matrice = malloc(sizeof(t_room**) * (elem.number_rooms + 1))))
		return (NULL);
	while (i < elem.number_rooms)
	{
		j = 0;
		if (!(new_matrice[i] = malloc(sizeof(t_room*) * elem.number_rooms)))
			return (NULL);
		while (j < elem.number_rooms)
		{
			new_matrice[i][j] = matrice[i][j];
			j++;
		}
		i++;
	}
	new_matrice[i] = NULL;
	return (new_matrice);
}

void		ft_free_matrice(t_room ***matrice)
{
	int			i;

	i = 0;
	while (matrice[i])
		free(matrice[i++]);
	free(matrice);
}