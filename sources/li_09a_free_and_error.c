/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_09a_free_and_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:32:29 by jdouniol          #+#    #+#             */
/*   Updated: 2019/02/18 05:32:30 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	ft_free_room
*/

void	ft_free_room(t_lst *lst)
{
	t_room	*room;

	room = (t_room*)lst;
	free(room->name_room);
	free(room->tab);
}

/*
**	ft_free_list
*/

void	ft_free_lst(t_lst *lst, void (*f)(t_lst *lst))
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
**	ft_free_all
*/

void	ft_free_all(t_all *elem)
{
	ft_free_lst((t_lst*)elem->room, ft_free_room);
	ft_putendl("je suis la");
}

/*
**	ft_free_them
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
**	ft_error_tube
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
**	ft_error
*/

void	ft_error(int nb)
{
	if (nb == ERROR)
	{
		write(STDERR_FILENO, "ERROR\n", 6);
		exit(1);
	}
}

/*
**	free_room
*/

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
**	ft_free_path
*/

void	ft_free_path(t_lst *lst)
{
	(void)lst;
}
