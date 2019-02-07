#include "../includes/lem_in.h"

t_path		*ft_bfs(t_all *elem, t_room ***matrice, int i_room, t_path *path)// i_room, d abord end, puis les autres // y ajouter un int de numero de path?
{
//	int i;
	int j;
	int max;
	int ret_j;
//	t_room ***matrice_tmp;
	t_path	*tmp;

	ft_printf("youplaboum\n");
	path->room = ft_init_end(elem);
	j = 0;
//	i = elem->end_id;
//	matrice_tmp = matrice;
	ft_printf("start_id: %d\n", elem->start_id);
	ft_printf("i_room: %d\n", i_room);
	while (j != elem->start_id || matrice[i_room][j] == NULL)
	{
		max = 2147483647;
		ft_printf("ici2 j = %d\n", j);
		while ( j < elem->number_rooms)
		{
			ft_printf("ici j = %d\n", j);
			ft_printf("ici ret_j = %d\n", ret_j);
			if (matrice[i_room][j] != NULL && matrice[i_room][j]->weight < max)
			{
				max = matrice[i_room][j]->weight;
				ret_j = j;
				ft_printf("i m in, here j = %d\n", j);
				ft_printf("i m in, here max = %d\n", max);
			}
			j++;
		}
		if (max == 2147483647)
			return (NULL);
		i_room = j;
		j = 0;
		ft_printf("path prev : %p\n", path->prev);

		if (path->prev == NULL)
			path->prev = ft_init_path();
		path->prev->room = ft_get_room_by_id(elem, ret_j);
		tmp = path;
		path = path->prev;
		path->prev = NULL;
		path->next = tmp;
		ft_bfs(elem, matrice, ret_j, path);
	}
	if (j == elem->start_id && matrice[i_room][j])
	{
		path->prev->room = ft_init_start(elem);
		path = path->prev;
		path->prev = NULL;
		ft_printf("youpi\n");
		print_path(path);
		return (path);
	}
	else
		return (NULL);
		//ft_bfs(elem, matrice, j )
}