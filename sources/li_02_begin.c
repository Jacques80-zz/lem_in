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

/*
**
*/

int		*ft_get_path(t_all *elem, int **matrice, int start, int end)
{
	int *tab_of_path;
	int i;
	int j;
	int size;

	size = 0;
	i = start;
	j = 0;
	if(!(tab_of_path = malloc(sizeof(int) * (elem->number_rooms + 1))))
		return (NULL);
	tab_of_path[size] = i;
	//ft_print_matrice(matrice, elem);
	while (elem->path_found == 0)//i != end && matrice[i][j] < 1)
	{
		ft_printf("je suis ici\n");
		while(j < elem->number_rooms && matrice[i][j] != 1)
			{
				j++;
				ft_printf("ici j = %d", j);
			}
		if (matrice[i][j] == 1)
		{
			matrice[i][j] = matrice[i][j] + 1;
			matrice[j][i] = matrice[j][i] + 1;
			size = size + 1;
			tab_of_path[size] = j; 
			i = 0;
		}
		while( i < elem->number_rooms && matrice[i][j] != 1)
			{i++;
			ft_printf("ici i = %d", i);}
		if (matrice[i][j] == 1)
		{
			matrice[i][j] = matrice[i][j] + 1;
			matrice[j][i] = matrice[j][i] + 1;
			size = size + 1;
			tab_of_path[size] = i; 
			j = 0;
		}
	}

	ft_print_matrice(matrice, elem);

	return (tab_of_path);
	//if ((i == end || j == end)  && matrice[i][j] == 1)

}
