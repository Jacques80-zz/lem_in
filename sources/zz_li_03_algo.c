#include "../includes/lem_in.h"

void	ft_print_path(int *tab_of_path)
{
	int i;

	i = 0;
	while(tab_of_path[i] >= 0)
	{
		ft_printf("~%d~",tab_of_path[i]);
		i++;
	} 
}

/*
typedef	struct 		s_room // 
{
	int 			room_id;
	int				number_ants_in_room; //nb_a
	char 			*name_room; //name
	int				coord_x_room; // x
	int				coord_y_room; // y
	int				*linked_to_start;
	int				*linked_to_end;
	int 			*names_path_available; //
	int				number_path_availbale;
	int				distance; // *distance ?
	int				compteur_from_start;
	int				compteur_from_end;
	int				you_should_not_pass;
	int				*linked_to;
	int				number_rooms_linked;
	struct s_room	*prev;
	struct s_room	*next;
	struct s_room	**tab;
	t_status		status;
	t_available		available;
}
*/

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
				ft_printf("%-10d", 0);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n\n\n");
}

int		ft_anybody_else_here(t_all *elen, t_room ***matrice, int current_room_id)
{
	int j;

	j = 0;
	while (j < elem->number_rooms)
	{
		if (matrice[current_room_id][j] != NULL && matrice[current_room_id][j]->weight < 0)
			return (1);
		else
			j++;
	}
	if (j == elem->number_rooms)
		return (0);

}

	int				*tmp_tab_room;
	int				size_tmp_tab_room;

int		ft_add_weight(t_all *elem, t_room ***matrice, int weight, int current_room_id)
{
	int i;
	int j;
	int k;
	t_room *tmp;

	i = current_room_id;
	j = 0;
	k = elem->end_id;
	while (ft_anybody_else_here(elem, matrice, i))
	{	
		while (j < elem->number_rooms)
		{
			if (matrice[i][j] && matrice[i][j]->weight == -1)
				{
					elem->tmp_tab_room[elem->size_tmp_tab_room] = j;
					elem->size_tmp_tab_room = elem->size_tmp_tab_room + 1;
					matrice[i][j]->weight == weight;
				}
			j++
		}
		if (j == elem->number_rooms)
		{
			while (elem->size_tmp_tab_room != 0)
			{
				i = elem->tmp_tab_room[elem->size_tmp_tab_room - 1];
				weight= weight + 1;
				ft_add_weight(elem, matrice, weight, i)
				elem->size_tmp_tab_room = elem->size_tmp_tab_room - 1;
			}
		}
	}
	ft_print_matrice_weight(matrice, elem);
}

/*
**
*/
/*
int		*ft_get_path(t_all *elem, int **matrice, int start, int end, int *delay) // TODO ecrire dans une matrice temporaire
{
	int *tab_of_path;
	int i;
	int j;
	int size;

	size = 0;
	i = start;
	j = 0;
	(void)end;
	if(!(tab_of_path = malloc(sizeof(int) * (elem->number_rooms * 2048))))
		return (NULL);
	tab_of_path[size] = i;
	//ft_print_matrice(matrice, elem);
	while (elem->path_found == 0)//i != end && matrice[i][j] < 1)
	{
	//	ft_printf("je suis ici\n");
		while(j < elem->number_rooms && matrice[i][j] != 1)
		{
			j++;
		//	ft_printf("ici j = %d", j);
		}
		if (j != elem->number_rooms && matrice[i][j] == 1)
		{
			matrice[i][j] = matrice[i][j] + 1;
			matrice[j][i] = matrice[j][i] + 1;
			size = size + 1;
			tab_of_path[size] = j;
			if ( i == end  || j == end)
			{
				elem->path_found = 1;
				break;
			//	ft_print_matrice(matrice, elem);	
			//	return (tab_of_path);
			}
			i = 0;
		}
		while( i < elem->number_rooms && matrice[i][j] != 1)
		{
			i++;
	//		ft_printf("ici i = %d", i);
		}
		if (i != elem->number_rooms && matrice[i][j] == 1)
		{
			matrice[i][j] = matrice[i][j] + 1;
			matrice[j][i] = matrice[j][i] + 1;
			size = size + 1;
			tab_of_path[size] = i; 
			if ( i == end  || j == end)
			{
				elem->path_found = 1;
				break;
			//	ft_print_matrice(matrice, elem);
			//	return (tab_of_path); 
			}
			j = 0;
		}
	//	if (i == elem->number_rooms)

	}
	size = size + 1;
	tab_of_path[size] = -1;
	ft_print_matrice(matrice, elem);
	ft_print_path(tab_of_path);
	return (tab_of_path);
	//if ((i == end || j == end)  && matrice[i][j] == 1)

}*/
