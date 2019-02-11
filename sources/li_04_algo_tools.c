#include "../includes/lem_in.h"
/*
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
*/

/*
t_path		*ft_rec_bfs(t_all elem, t_room ***matrice, t_path *path) // je n arrive pas a le faire fonctionner
{
	int i;
	int j;
	int ret_j;
	int min_weight;
	t_path	*tmp;

//	print_path(path);
	i = path->room->room_id;
	j = 0;
//	t_room ***matrice_tmp; // avoir une copie de matrice
	ret_j = -1;
	min_weight = -1;
//	ft_print_matrice_weight(matrice, &elem);
	if (path->room->status == START)
	{
		print_path(path);
		return (path);
	}
	while (j < elem.number_rooms)
	{
		if (matrice[i][j] && matrice[i][j]->available == VISITED)
		{
			if ((matrice[i][j]->weight < min_weight || min_weight == -1))
			{
				min_weight = matrice[i][j]->weight;
				ret_j = j;
			}
		}
		else
		j++;
	}
	if (ret_j == -1)
		return (NULL);
	tmp = ft_init_path(matrice[i][ret_j]);
	tmp->room = matrice[i][ret_j];
	tmp->next = path;
	path->prev = tmp;
	path = tmp;
	matrice[i][ret_j]->available = POSSIBLE_PATH;
	return (ft_rec_bfs(elem, matrice, path));
}
*/

int			ft_there_is_no_other_room_free(t_all elem, t_room **matrice)
{
	int j;
//	int i;
	int visited;

//	i = 0;
	j = 0;
	visited = 0;
	while(j < elem.number_rooms)
	{
		if (matrice[j] && matrice[j]->available == VISITED)
			visited++;
		j++;
	}
	if (visited == 0)
		{	
			ft_printf("no other rooms possible\n");
			return (1);
		}
	else
		{	
			ft_printf("there is other rooms possible\n");
			return (0);
		}
}

int		there_is_still_at_least_one_room_possible_path(t_all elem, t_room ***matrice_cpy, int path_id, int i)
{
	int j;

	j = 0;
	while (j < elem.number_rooms)
	{
		if (matrice_cpy[i][j] == NULL || matrice_cpy[i][j]->available !=POSSIBLE_PATH
			|| (matrice_cpy[i][j]->available == POSSIBLE_PATH && matrice_cpy[i][j]->possible_path_id != path_id))
			j++;
		else 
			break;
	}
	if (j == elem.number_rooms)
		return (0);
	else
		return (1);
}

int		ft_remove_possible_path_status(t_all elem, t_room ***matrice_cpy, int path_id, int i)
{
	int j_tmp;
	int ret_j;

	if (i == -2)
		return (-2);
	ret_j = -1;
	j_tmp = 0;
	while(j_tmp < elem.number_rooms)
	{
		if (matrice_cpy[i][j_tmp] == NULL || matrice_cpy[i][j_tmp]->available !=POSSIBLE_PATH
			|| (matrice_cpy[i][j_tmp]->available == POSSIBLE_PATH && matrice_cpy[i][j_tmp]->possible_path_id != path_id))
				continue;//j_tmp++;
		else if (matrice_cpy[i][j_tmp]->available == POSSIBLE_PATH && matrice_cpy[i][j_tmp]->possible_path_id == path_id)
		{
			ret_j = j_tmp;
			matrice_cpy[i][j_tmp]->available = VISITED;
			matrice_cpy[i][j_tmp]->possible_path_id = 0;
			ft_remove_possible_path_status(elem, matrice_cpy, path_id, j_tmp);
		}
		j_tmp++;
	}
	return (ret_j > -1 ? ret_j : -2);
}

int 		ft_there_is_no_other_room_linked_with_less_weight(t_all elem, t_room ***matrice_cpy, int min_weight, int i)
{
	int k;

	k = 0;
	while (k < elem.number_rooms)
	{
		if (matrice_cpy[i][k] && matrice_cpy[i][k]->weight < min_weight && matrice_cpy[i][k]->available == VISITED)
			return (1);
		k++;
	}
	return (0);
}
/*
t_path		*ft_rec_bfs(t_all elem, t_room ***matrice, t_path *path, t_room ***matrice_cpy, int path_id) // je n arrive pas a le faire fonctionner
{
	int i;
	int j;
	int ret_j;
	int min_weight;
	t_path	*tmp;

//	print_path(path);
	i = path->room->room_id;
	j = 0;
//	t_room ***matrice_tmp; // avoir une copie de matrice
	ret_j = -1;
	min_weight = -1;
//	ft_print_matrice_weight(matrice, &elem);
	if (path->room->status == START)
	{
		ft_printf("voila le path retourne:\n");
		print_path(path); // + ecrire path qqpart // ok grace au main?
		elem.path_id++;
		return (path);
	}
	while (j < elem.number_rooms)
	{
		if (matrice_cpy[i][j])ft_printf("ici weight = %d, min_weight = %d i = %d, j = %d\n", min_weight, matrice_cpy[i][j]->weight, i, j); // c est ici le bordel
		if (matrice_cpy[i][j] && matrice_cpy[i][j]->available == VISITED)
		{
			if ((matrice_cpy[i][j]->weight < min_weight || min_weight == -1))
			{
				min_weight = matrice_cpy[i][j]->weight;
				ret_j = j;
				if (ft_there_is_no_other_room_linked_with_less_weight(elem, matrice_cpy, min_weight, i))
					break;
			}
		}
		if (matrice_cpy[i][j] && matrice_cpy[i][j]->available == POSSIBLE_PATH)//&& matrice_cpy[i][j]->weight < matrice_cpy )
		{
			ft_printf("i m nowhere \n");
			ft_printf("ici weight = %d, min_weight = %d i = %d, j = %d\n", min_weight, matrice_cpy[i][j]->weight, i, j);
			ft_print_matrice_weight(matrice_cpy, &elem);
			ft_print_status_room(matrice_cpy, &elem);
			if (ft_there_is_no_other_room_free(elem, matrice_cpy[i])) // ajouter une condition si une autre room mene vers nulle part?
			{

			// si i = elem->end_id ca veut dire que nous avons sette toutes les rooms qui partaient de end, c'est bon, sinon verifier que le nmbre de possible path est different de facteur limitant
				ft_printf("i m here \n");
				ft_delete_just_one_link_and_change_status(elem, matrice_cpy, i, j, matrice_cpy[i][j]->possible_path_id);
				path = ft_init_path(ft_init_end(&elem));
				ft_rec_bfs(elem, matrice, path, matrice_cpy, elem.path_id);
				//break;
					// kicker lien qui va vers end dans matrice tmp
				// mettre le statut de chaque room de ce path a VISITED
			}
			else if (!(ft_there_is_no_other_room_free(elem, matrice_cpy[i])))
			{
				min_weight = -1;
				ft_printf("let's look for this other room \n");
			}
		}
		ft_printf("j++ \n");
		j++;
	}
	if (ret_j == -1)
		return (NULL);
	ft_printf("boucle finie ici ret_j = %d \n", ret_j);

	ft_printf("boucle finie ici min_weight = %d \n", min_weight);
//	ft_print_status_room(matrice_cpy, &elem);
	tmp = ft_init_path(matrice_cpy[i][ret_j]);
	matrice_cpy[i][ret_j]->possible_path_id = path_id; // TODO verifier qu on ne l ecrit jamais dans end
	matrice_cpy[i][ret_j]->available = POSSIBLE_PATH;
	ft_print_status_room(matrice_cpy, &elem);
	//matrice_cpy[ret_j][i]->possible_path_id = path_id;
	tmp->room = matrice_cpy[i][ret_j];
	tmp->next = path;
	path->prev = tmp;
	path = tmp;
//	matrice_cpy[ret_j][i]->available = POSSIBLE_PATH;
	return (ft_rec_bfs(elem, matrice, path, matrice_cpy, elem.path_id));
}
*/

void		ft_remove_possible_path_status2(t_all elem, t_room ***matrice_cpy, int path_id, int i)
{
	int j;
	int k;

	(void)i;
	j = 0;
	k = 0;
	ft_printf("remove status \n");
	while (k < elem.number_rooms)
	{
		while (j < elem.number_rooms)
		{
			if (matrice_cpy[k][j] && matrice_cpy[k][j]->possible_path_id == path_id && matrice_cpy[k][j]->available == POSSIBLE_PATH)
			{
				matrice_cpy[k][j]->available = VISITED;
				matrice_cpy[k][j]->possible_path_id = 0;
				ft_printf("ici on enleve le possible path de i: %d et j : %d", i , j);
			}
			j++;
		} 
		k++;
	}
	ft_print_status_room(matrice_cpy, &elem);
}

void		ft_cancel_link(t_all elem, t_room ***matrice_cpy, int i, int j, int path_id)
{
	(void)i;
	(void)elem;

	int path;
	int i_tmp;
	int weight;
	int j_tmp;
	int close_weight;

	ft_printf("debut du cancel ici j vaut : %d", j);
	close_weight = INT_MAX;
	j_tmp = 0;
	i_tmp = j;
	path = matrice_cpy[i][j]->possible_path_id;
	weight = matrice_cpy[i][j]->weight;
	while (j_tmp < elem.number_rooms)
	{
		if (matrice_cpy[i_tmp][j_tmp] && matrice_cpy[i_tmp][j_tmp]->possible_path_id == path_id)
		{
			if (matrice_cpy[i_tmp][j_tmp]->weight > weight)
			{
				matrice_cpy[i_tmp][j_tmp]->weight = -1;
				ft_printf("je suprime le lien i = %d, j = %d", i_tmp, j_tmp);
				matrice_cpy[j_tmp][i_tmp]->weight = -1;
				matrice_cpy[i_tmp][j_tmp] = NULL;
				matrice_cpy[j_tmp][i_tmp] = NULL;

				return;
			} 
		}
		j_tmp++;
	}
	ft_printf("ici path id : %d", path_id);
	ft_remove_possible_path_status2(elem, matrice_cpy, path_id, i);
	ft_add_weight(elem, matrice_cpy, 0, ft_init_start(&elem));
	ft_print_matrice(matrice_cpy, &elem);
//	ft_add_weight(elem, matrice_cpy, 0, ft_init_start(&elem));
	ft_print_matrice_weight(matrice_cpy, &elem);
}
/*
int		ft_delete_just_one_link_and_change_status(t_all elem, t_room ***matrice_cpy, int i, int j, int path_id)
{
	int i_tmp;
	int j_tmp;
	int weight;

	i_tmp = j;
	j_tmp = 0;
	weight = elem.matrice[i][j]->weight;
	while (j_tmp < elem.number_rooms)
	{
		if (matrice_cpy[i_tmp][j_tmp] && matrice_cpy[i_tmp][j_tmp]->available == POSSIBLE_PATH
			&& matrice_cpy[i_tmp][j_tmp]->weight > weight
				&& matrice_cpy[i_tmp][j_tmp]->possible_path_id == path_id)
					//&& j_tmp != elem->end_id)
		{
			ft_printf("lala i_tmp : %d, j_tmp : %d\n", i_tmp, j_tmp);
			matrice_cpy[i_tmp][j_tmp] = NULL;
//			matrice_cpy[j_tmp][i_tmp] = NULL;
			i = j_tmp;
		}
		j_tmp++;
	}
	//while (there_is_still_at_least_one_room_possible_path(elem, matrice_cpy, path_id, i))
	//{
	//	 ft_remove_possible_path_status(elem, matrice_cpy, path_id, i);
	ft_printf("i m deleting\n");
	ft_print_matrice(matrice_cpy, &elem);
	ft_print_matrice_weight(matrice_cpy, &elem);
	ft_print_status_room(matrice_cpy, &elem);
	ft_remove_possible_path_status2(elem, matrice_cpy, path_id, i);
	//}
	return (0);
}
*/

void		ft_print_matrice_debug(t_all elem, t_room ***matrice_cpy, int path_id)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < elem.number_rooms)
	{
		while(j < elem.number_rooms)
		{
			if (matrice_cpy[i][j] && matrice_cpy[i][j]->possible_path_id == path_id)
				ft_printf("yolo ici i: %d, j %d\n", i , j) && ft_printf("path_id %d\n", matrice_cpy[i][j]->possible_path_id);
			j++;
		}
		i++;
	}
}

t_path		*ft_rec_bfs2(t_all elem, t_room ***matrice, t_path *path, t_room ***matrice_cpy, int path_id)
{
	int i;
	int j;
	int ret_j;
	t_path *tmp;
	int min_weight;

	min_weight = -1;
	ret_j = 0;
	i = path->room->room_id;
	j = 0;
	print_path(path);
	if (path->room->status == START)
	{
		ft_printf("voila le path retourne:\n");
		print_path(path); // + ecrire path qqpart // ok grace au main?
		elem.path_id++;
		return (path);
	}
	ret_j = -1;
	while (j < elem.number_rooms)
	{
		ft_printf("i = %d, j = %d, ret_j = %d\n", i, j, ret_j);
		if (matrice_cpy[i][j] && matrice_cpy[i][j]->available == VISITED)
		{
			if ((matrice_cpy[i][j]->weight < min_weight || min_weight == -1))
			{
				min_weight = matrice_cpy[i][j]->weight;
				ret_j = j;
			}
		}
		if (matrice_cpy[i][j] && matrice_cpy[i][j]->available == POSSIBLE_PATH)
		{
			ft_printf("i = %d, j = %d\n", i, j);
			ft_printf("i = %d, ret_j = %d\n", i, ret_j);
			if (ft_there_is_no_other_room_free(elem, matrice[i]))
			{
				ft_printf("on est la, on s apprete a supprimer des liens \n");
				ft_printf("ici possible_path_id = \n", matrice[i][j]->possible_path_id);
				//ft_print_matrice(matrice_cpy, &elem);
				ft_cancel_link(elem, matrice_cpy, i, j, matrice[i][j]->possible_path_id);
				//ft_print_matrice(matrice_cpy, &elem);
				ft_print_status_room(matrice_cpy, &elem);
				print_path(path);
				print_path(path);
				print_path(path);
				ft_printf("path room id : %d\n", path->room->room_id);
				ft_print_matrice_debug(elem, matrice_cpy, path_id);
				ft_add_weight(elem, matrice, 0, ft_init_start(&elem));
				ft_rec_bfs2(elem, matrice, path, matrice_cpy, elem.path_id);
			//	ft_print_matrice(matrice_cpy, &elem);
				break;
			//	annuler le lien de la room problematique vers end;
			//	mettre tout le chemin en VISITED plutot que POSSIBLE_PATH;
			}

		}
		j++;	
	}
	if (ret_j != -1)
	{
	tmp = ft_init_path(matrice_cpy[i][ret_j]);
	ft_printf("ici i= %d, ret_j = %d, path_id = %d\n", i, ret_j, path_id);
	ft_printf("possible path de matrice i j = %d\n", matrice_cpy[i][ret_j]->possible_path_id);
	matrice_cpy[i][ret_j]->possible_path_id = path_id; // TODO verifier qu on ne l ecrit jamais dans end
	matrice_cpy[i][ret_j]->available = POSSIBLE_PATH;
	ft_print_status_room(matrice_cpy, &elem);
	tmp->room = matrice_cpy[i][ret_j];
	tmp->next = path;
	path->prev = tmp;
	path = tmp;
	}
	else
		return (NULL);
//	matrice_cpy[ret_j][i]->available = POSSIBLE_PATH;
	return (ft_rec_bfs2(elem, matrice, path, matrice_cpy, elem.path_id));

}



t_path		*ft_bfs(t_all elem, t_room ***matrice, t_path *path)
{
	int i;
	int j;
	int ret_j;
	int min_weight;
	t_path	*tmp;

//	print_path(path);
	i = path->room->room_id;
	j = 0;
//	t_room ***matrice_tmp; // avoir une copie de matrice
	ret_j = -1;
	min_weight = -1;
//	ft_print_matrice_weight(matrice, &elem);
	if (path->room->status == START)
	{
		print_path(path);
		return (path);
	}
	while (j < elem.number_rooms)
	{
		if (matrice[i][j])
		{
			if ((matrice[i][j]->weight < min_weight || min_weight == -1))
			{
				min_weight = matrice[i][j]->weight;
				ret_j = j;
			}
		}
		j++;
	}
	if (ret_j == -1)
		return (NULL);
	tmp = ft_init_path(matrice[i][ret_j]);
	tmp->room = matrice[i][ret_j];
	tmp->next = path;
	path->prev = tmp;
	path = tmp;
	return (ft_bfs(elem, matrice, path));
}