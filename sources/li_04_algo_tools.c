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

t_path		*ft_bfs(t_all elem, t_room ***matrice, t_path *path) // TODO ajouter matrice temp
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
		return (path);
	}
	while (j < elem.number_rooms)
	{
		if (matrice[i][j])
		{
			if ((matrice[i][j]->weight < min_weight || min_weight == -1))
			{
//				ft_putendl("je suis la");
				min_weight = matrice[i][j]->weight;
				ret_j = j;
			}
		}
		j++;
	}
/*	if (path->prev == NULL)
			path->prev = ft_init_path(matrice[i][ret_j]);
	path->prev->room = matrice[i][ret_j];
	tmp = path;
	path = path->prev;
	path->prev = NULL;
	path->next = tmp;
*/

//	ft_printf("ret_j = %d, min_weight = %d\n", ret_j, min_weight);
//	if (ret_j == -1 || min_weight == -1)
//		ft_printf("ret_j = %d || min_weight = %d\n", ret_j, min_weight);
	if (ret_j == -1)
		return (NULL);
	tmp = ft_init_path(matrice[i][ret_j]);
	if (!tmp)
		ft_printf("tmp est NULL\n");
	tmp->room = matrice[i][ret_j];
	tmp->next = path;
	path->prev = tmp;
	path = tmp;
	return (ft_bfs(elem, matrice, path));
}
// 	TODO ajouter matrice_tmp a la fonction bfs et a son appel
//	TODO ecrire path dans matrice temp avec pour valeur 2 
//	TODO si on croise un chemin qui est deja possiblement utilise on sette a 0 les liens entre toutes les salles reliees par possible path et uniquement a celle ci, en remontant vers start
//	TODO rappeler bfs avec matrice temp tant que le nombre de matrice_tmp[i_end][j++] egal a  2 est inferieur a (ft_minimun(nombre de salles reliees a end / facteur limitant)) // peut etre pas toujours pertinent a voir

//	TODO de plus tard le dispatch des fourmies dans chaque path quand on en sera la on sera bien
// 	TODO cas d erreur / gestion des leaks / norminette
