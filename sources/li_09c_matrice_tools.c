#include "../includes/lem_in.h"

int			**create_matrice_flow(t_all elem)
{
	int		i;
	int		j;
	int		**matrice;

	i = 0;
	if (!(matrice = malloc(sizeof(int*) * (elem.number_rooms + 1))))
		return (NULL);
	while (i < elem.number_rooms)
	{
		j = 0;
		if (!(matrice[i] = malloc(sizeof(int) * elem.number_rooms)))
			return (NULL);
		while (j < elem.number_rooms)
		{
			matrice[i][j] = 0;
			j++;
		}
		i++;
	}
	matrice[i] = 0;
	return (matrice);
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

int			**matrice_flow_cpy(t_all elem, int **matrice)
{
	int				i;
	int				j;
	int				**new_matrice;

	i = 0;
	if (!(new_matrice = malloc(sizeof(int*) * (elem.number_rooms + 1))))
		return (NULL);
	while (i < elem.number_rooms)
	{
		j = 0;
		if (!(new_matrice[i] = malloc(sizeof(int) * elem.number_rooms)))
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

void		ft_free_matrice_flow(int **matrice)
{
	int			i;

	i = 0;
	while (matrice[i])
		free(matrice[i++]);
	free(matrice);
}
