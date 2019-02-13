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

void	print_room_flow(t_all elem, int nb)
{
	int			i;

	i = 0;
	while (i++ < nb)
		elem.room = elem.room->next;
	ft_printf("%-9s|", elem.room->name_room);
}

void	print_all_name_flow(t_all elem)
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


void	ft_print_matrice_flow(int **matrice, t_all *elem)
{
	int i;
	int j;

	i = 0;
	print_all_name_flow(*elem);
	while (i < elem->number_rooms)
	{
		j = 0;
		print_room_flow(*elem, i);
		while (j < elem->number_rooms)
		{
			ft_printf("%-10d", matrice[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n\n\n");
}



void			break_start_end(t_all elem, t_room ***matrice)
{
	int				start_id;
	int				end_id;
	t_room			*tmp;
	int				i;
	int				j;

	start_id = 0;
	end_id = 0;
	tmp = elem.room;
	while (tmp && (!start_id || !end_id))
	{
		if (tmp->status == START)
			start_id = tmp->room_id;
		if (tmp->status == END)
			end_id = tmp->room_id;
		tmp = tmp->next;
	}
	i = 0;
	j = start_id;
	while (i < elem.number_rooms)
		matrice[i++][j] = NULL;
	i = end_id;
	j = 0;
	while (j < elem.number_rooms)
		matrice[i][j++] = NULL;
}

void			add_path(t_path **path, t_room *room)
{
	t_path		*new;
	t_path		*tmp;

	if (!(new = malloc(sizeof(t_path))))
		return ;
	new->room = room;
	new->next = NULL;
	if (!*path)
		*path = new;
	else
	{
		tmp = *path;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}

}

void			push_file(t_files **files, t_room *room, t_path *path)
{
	t_files		*new;
	t_files		*tmp;

	if (!(new = malloc(sizeof(t_files))))
		return ;
	new->room = room;
	add_path(&path, room);
	new->path = path;
	new->next = NULL;
	if (!*files)
		*files = new;
	else
	{
		tmp = *files;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_files			*pop_file(t_files **file)
{
	t_files		*tmp;

	tmp = *file;
	(*file) = (*file)->next;
	return (tmp);
}

t_path			*path_cpy(t_path *path)
{
	t_path			*new;

	new = NULL;
	while (path)
	{
		add_path(&new, path->room);
		path = path->next;
	}
	return (new);
}

int				is_not_in_path(t_path *path, t_room *room)
{
	while (path)
	{
		if (path->room == room)
			return (0);
		path = path->next;
	}
	return (1);
}

t_path			*ft_bfs_(t_all elem, t_room ***matrice, int **matrice_flow, t_room *start, int bfs)
{
	int				i;
	int				j;
	t_files			*file;
	t_files			*tmp;

	file = NULL;
	push_file(&file, start, NULL);
	while (file)
	{
		tmp = pop_file(&file);
		i = tmp->room->room_id;
		j = 0;
		if (tmp->room->status == END)
			return (tmp->path);
		while (j < elem.number_rooms)
		{
			if (matrice[i][j] && matrice_flow[i][j] != 1 && is_not_in_path(tmp->path, matrice[i][j]) && matrice[i][j]->bfs != bfs)
			{
				matrice[i][j]->bfs = bfs;
				push_file(&file, matrice[i][j], path_cpy(tmp->path));
			}
			j++;
		}
	}
	return (NULL);
}

void			put_flow_in_matrice( int **matrice_flow, t_path *path)
{
	int			i;
	int			j;

	while (path->room->status != END)
	{
		i = path->room->room_id;
		j = path->next->room->room_id;
		matrice_flow[i][j]++;
		path = path->next;
	}
}

void			delete_bad_link(t_all elem, int **matrice_flow)
{
	int			i;
	int			j;

	i = 0;
	while (i < elem.number_rooms)
	{
		//printf("dwefefwefe\n");
		j = 0;
		while (j < elem.number_rooms)
		{
			if (matrice_flow[i][j] && matrice_flow[j][i])
			{
				matrice_flow[i][j] = 0;
				matrice_flow[j][i] = 0;
			}
			j++;
		}
		i++;
	}
}

int				edmond_karp(t_all elem, t_room ***matrice, int **matrice_flow, t_room *start)
{
	t_path		*path;
	int			bfs;

	bfs = 0;
	while ((path = ft_bfs_(elem, matrice, matrice_flow, start, bfs++)))
	{
		print_path(path);
		put_flow_in_matrice(matrice_flow, path);
		delete_bad_link(elem, matrice_flow);
	}
//	ft_print_matrice_flow(matrice_flow, &elem);
	return (1);
}
