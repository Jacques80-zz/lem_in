/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_01ter_parse_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:30:57 by jdouniol          #+#    #+#             */
/*   Updated: 2019/02/18 05:31:02 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		ft_print_infos(t_all *elem)
{
	t_map		*tmp;

	tmp = elem->map;
	while (elem->map != NULL)
	{
		tmp = elem->map->next;
		ft_printf("%s\n", elem->map->str);
		free(elem->map->str);
		free(elem->map);
		elem->map = tmp;
	}
	ft_printf("\n");
}

void			ft_init_elem(t_all *elem)
{
	elem->number_ants = 0;
	elem->number_rooms = 0;
	elem->room = NULL;
	elem->matrice_init = 0;
	elem->matrice = NULL;
	elem->map = NULL;
	elem->next_is_start = 0;
	elem->next_is_end = 0;
	elem->shortest_path = NULL;
	elem->start_id = -1;
	elem->end_id = -1;
	elem->bfs = 0;
}

int				ft_read(t_all *elem)
{
	int		i;
	char	*line;

	ft_init_elem(elem);
	i = GNL_LINE_READ;
	line = NULL;
	while (i == GNL_LINE_READ)
	{
		line = NULL;
		if ((i = get_next_line(STDIN_FILENO, &line)) == GNL_ERROR)
			return (FAIL);
		if (i == GNL_END)
		{
			free(line);
			break ;
		}
		if (ft_get_instructions(elem, line) == ERROR)
		{
			free(line);
			return (ERROR);
		}
		ft_save_map(elem, line);
		free(line);
	}
	return (SUCCESS);
}
