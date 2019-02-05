#include "../includes/lem_in.h"
# include <stdarg.h>

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

/*
**	ft_init_elem est appele au debut de ft_read
**	elle met tous les int a 0 et les tableaux (char ou room) a NULL
*/

void			ft_init_elem(t_all *elem)
{
	elem->number_ants = 0;
	elem->number_rooms = 0;
	elem->limited_factor = 0;
	elem->nbr_lines_in_file = 0;
//	elem->line = NULL;
	elem->room = NULL;
	elem->path_found = 0;
	elem->matrice_init = 0;
	elem->matrice = NULL;
}

/*
**	ft_read est appele au debut du lem in
**	il lit le fichier entre en parametre ligne par ligne 
**	Si GNL renvoie une erreur (-1) le programme s'arrete ici (apres avoir free)
**	tant que get_instructions est valide, on enregistre les datas avec
**		ft_save_map
**	Si get_instructions lit une ligne invalide, on checke si l'ensemble de la
**	map lue ( a ce stade donc save dans elem)  permet d'aller de start a end
**	Si oui retourne ERROR (1), sinon retourne FAIL (2)
**	Si GNL = 0, on checke si la charte est resolvable
**	Si oui on retourne SUCCESS, sinon retourne FAIL
*/

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
			return (ERROR);//( Si carte reseolvable ? ERROR : FAIL); //cas ou la carte esr resolvable malgre une ligne d'erreur
		}
		ft_save_map(elem, line);
		free(line);
	}
	return (SUCCESS);//(Si carte resolvable) ? SUCCESS : FAIL); //  if path found retourne success sinon fail
}

/*
**	Imprime toute la map jusqu'a la derniere ligne valide
*/

void	ft_print_infos(t_all *elem)
{
	while (elem->map != NULL)
	{
		ft_printf("%s\n", elem->map->str);
		elem->map = elem->map->next;
	}
}

/*
**	Le main quoi, d'abord les cas d erreur de ft_read, puis on cherche
**	si un chemin est possible, si oui, on active le dispatch, si non
**	on free le tout avant de quitter
*/

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
	{	
			//	if (ft_init_ant(&elem) == SUCCESS)
		ft_print_matrice(elem.matrice, &elem);
		ft_print_infos(&elem); // a faire
//		ft_print_path(&elem); // a faire
	}
	/*
		if (ft_init_ant(&a) == SUCCESS)
	{
		if (ft_algo(&a) == ERROR)
		{
			ft_fruit_a(&a);
			return (EXIT_FAILURE);
		}
		ft_dispatch(&a);
	}
	ft_fruit_a(&a);
	*/
}