#include "../includes/lem_in.h"

/*
** 
*/

void	ft_free_room(t_lst *lst)
{
	t_room	*room;

	room = (t_room*)lst;
	free(room->name_room);
	free(room->tab);
}

/*
**
*/

void		ft_free_lst(t_lst *lst, void (*f)(t_lst *lst))
{
	t_lst	*free_lst;

	while (lst)
	{
		free_lst = lst;
		lst = lst->next;
		f(free_lst);
		free(free_lst);
	}
}

/*
**
*/

void		ft_free_all(t_all *elem)
{
//	int		i;

	ft_free_lst((t_lst*)elem->room, ft_free_room);	
//	free(elem->ant);
	ft_putendl("je suis la");
//	if (elem->tab_path)
//	{
//		i = -1;
//		while (elem->tab_path[++i])
//			ft_free_lst((t_lst*)elem->tab_path[i], ft_free_path);
//		free(elem->tab_path);
//	}
}

/*
**
*/

int		ft_free_them(size_t n, ...)
{
	void	*del;
	va_list	ap;

	va_start(ap, n);
	while (n-- > 0)
	{
		free((del = va_arg(ap, void *)));
		del = NULL;
	}
	va_end(ap);
	return (1);
}

/*
**
*/

int		ft_error_tube(char ***tab_tube)
{
	int		i;

	i = -1;
	while ((*tab_tube)[++i])
		free((*tab_tube)[i]);
	ft_free_them(1, *tab_tube);
	return (ERROR);
}

/*
**
*/

void	ft_error(int nb)
{
	if (nb == ERROR)
	{
		write(STDERR_FILENO, "Error\n", 6);
		exit(1);
	}
}

void	free_room(t_room *room)
{
	t_room	*tmp;

	while (room)
	{
		tmp = room->next;
		free(room->name_room);
		free(room->tab);
		room = tmp;
	}
}

/*
**
*/

void	ft_free_path(t_lst *lst)
{
	(void)lst;
}