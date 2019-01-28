#include "../includes/lem_in.h"

	/*
	struct s_path *tab;

	tab = malloc( 10 * sizeof(struct s_path) );

	tab[2].distance = 0;

*/

/*
malloc de s_room

faire
ft_free_all
ft_get_instructions
ft_save_map
ft_init_ant
ft_print_path
ft tube
ft_coord
ft_check_nb_ants
	*/
# include <stdarg.h>

void			ft_init_elem(t_all *elem)
{
	elem->number_ants = 0;
	elem->number_rooms = 0;
	elem->limited_factor = 0;
	elem->nbr_lines_in_file = 0;
	elem->line = NULL;
	elem->room = NULL;
	elem->path_found = 0;
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
			return (FAIL); // fail = 2
		if (i == GNL_END) // soit 0
		{
			free(line);
			break ;
		}
		if (ft_get_instructions(elem, line) == ERROR)
		{
			free(line);
			return (FAIL);//( Si carte reseolvable ? ERROR : FAIL); //cas ou la carte esr resolvable malgre une ligne d'erreur
		}
		ft_save_map(elem, line);
		free(line);
	}
	return (SUCCESS);//(Si carte resolvable) ? SUCCESS : FAIL); //  if path found retourne success sinon fail
}

void	ft_print_infos(t_all *elem)
{
	while (elem->map != NULL)
	{
		ft_printf("%s\n", elem->map->str);
		elem->map = elem->map->next;
	}
}

int				main(int ac, char **av)
{
	t_all		elem;

	(void)av;
	(void)ac;
	if (ft_read(&elem) == FAIL)
	{
		ft_free_all(&elem);
		ft_printf("Error\n");
		return (EXIT_FAILURE);
	}
	else
//	if (ft_init_ant(&elem) == SUCCESS)
	{	
		ft_print_infos(&elem); // a faire
//		ft_print_path(&elem); // a faire
	}
}