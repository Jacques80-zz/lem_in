#include "../includes/lem_in.h"

/*void		ft_add_weight(t_all elem, t_room ***matrice, int weight, t_room *start) // voir si en largeur n est pas plus rapide
{
	int				i;
	int				j;

	i = start->room_id;
	j = 0;
//	matrice[j][i]->weight = weight;
	if (start->weight == -1 || start->weight >= weight)
		start->weight = weight;
	if (start->status == END && (start->weight >= weight || start->weight == -1))
	{
		start->weight = weight;
		return;
	}
	while (j < elem.number_rooms)
	{
		if (matrice[i][j])
		{
			if (matrice[i][j]->weight >= weight || matrice[i][j]->weight == -1)
			{
			//	matrice[j][i]->weight = weight;
				ft_add_weight(elem, matrice, weight + 1, matrice[i][j]);
			}
		}
		j++;
	}
}*/

void		add_file(t_files **file, t_room *room)
{
	t_files		*new;
	t_files		*tmp;

	if (!(new = malloc(sizeof(t_files))))
		return ;
	new->room = room;
	new->next = NULL;
	if (!*file)
		*file = new;
	else
	{
		tmp = *file;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_room		*remove_file(t_files **file)
{
	t_room		*tmp;
	t_files		*temp;

	temp = *file;
	tmp = (*file)->room;
	*file = (*file)->next;
	free(temp);
	return (tmp);
}


void		ft_add_weight(t_all elem, t_room ***matrice, int weight, t_room *start) // voir si en largeur n est pas plus rapide
{
		int			i;
		int			j;
		t_files		*file;
		t_room		*tmp;

		add_file(&file, start);
		start->weight = weight;
		start->available = VISITED;
		while (file)
		{
			tmp = remove_file(&file);
			i = tmp->room_id;
			j = 0;
			while (j < elem.number_rooms)
			{
				if (matrice[i][j] && matrice[i][j]->available != VISITED)
				{
					add_file(&file, matrice[i][j]);
					matrice[i][j]->available = VISITED;
					matrice[i][j]->weight = tmp->weight + 1;
				}
				j++;
			}
		}
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
