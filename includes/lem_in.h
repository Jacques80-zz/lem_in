#ifndef LEM_IN_H
# define LEM_IN_H

# define SUCCESS		0
# define ERROR			1
# define FAIL			2
# define PATH_FOUND		3
# define PATH_END		4

# include "libft.h"
# include <stdio.h>

/*
gestion d'erreurs:
aucune salle OK
aucune fourmi OK
absence de start et/ou end (qui concerne toujours la ligne suivante) OK
ne prendre en compte que le dernier start / end pas encore
aucun chemin possible pas encore
multipath complexe pas encore
// une salle definie deux fois donc redefinie // coordonnées redefinies
// un tiret dans la salle? // OK considere comme erreur

gestion des commentaires:
accepter les commentaires ok

commandes autre que start et end // ?? ##debug?

Format de sortie

composition de la fourmilire doit etre repetee sur la sortie
les commandes et commentaires sont repetes sur la sortie
chemin au bon format 1 ligne par tour et N deplacements par tour, Lx-y (x fourmi y salle)

validité du chemin
*/



typedef enum		e_status // pour room
{
	START, END, NOT
}					t_status;

typedef enum		e_available // pour room // pertinent pour multipath complexe?
{
	VISITED, NO_VISITED, POSSIBLE_PATH, PATH // gerer le possible path
}					t_available;

typedef struct		s_map
{
	struct s_map	*next;
	char			*str;
	//e_type		type;
}					t_map;

typedef	struct 		s_room // 
{
	int 			room_id;
	int				number_ants_in_room; //nb_a
	char 			*name_room; //name
	int				coord_x_room; // x
	int				coord_y_room; // y
	int				*linked_to_start;
	int				*linked_to_end;
	int 			*names_path_available; //
	int				number_path_availbale;
	int				weight; // *distance ?
	int				compteur_from_start;
	int				compteur_from_end;
	int				you_should_not_pass;
	int				*linked_to;
	int				number_rooms_linked;
	int				bfs;
	struct s_room	*prev;
	struct s_room	*next;
	struct s_room	**tab;
	t_status		status;
	t_available		available;

}					t_room; 

typedef struct				s_path
{
	t_room			*room;
	struct s_path	*prev;
	struct s_path	*next;
}							t_path;

typedef struct				s_tab_path
{
	t_path				*path;
	int 				path_size;
	int 				nb_ant;
	int 				cumul;
	struct s_tab_path	*prev;
	struct s_tab_path	*next;
}							t_tab_path;

typedef struct 				s_ant
{
		t_path 			*path;
		t_path 			*tmp_path;
		int 			nb;
		struct s_ant	*prev;
		struct s_ant	*next;
}							t_ant;

typedef struct 		s_all
{
	int 			number_ants;
	int				number_rooms;
	int				limited_factor; // a voir si utile et comment il peut l etre 
	int 			nbr_lines_in_file;
//	t_line			*line; // lourd pour rien
	t_room			*room;
	int				path_found;
	t_tab_path		**tab_path;
	int				next_is_start;
	int				next_is_end;
	t_room			**ant;
	t_map			*map;
	t_room			*cur;
	t_room			***matrice;
	int				**matrice_flow;
	int 			matrice_init;
	int 			all_rooms_are_parsed;
	int				start_id;
	int				end_id;
	int				*tmp_tab_room;
	int				size_tmp_tab_room;

	t_path 			*shortest_path;
	int 			flow_max;
}					t_all;

typedef struct		s_lst
{
	struct s_lst	*next;
}					t_lst;

typedef struct		s_files
{
	t_room			*room;
	t_path			*path;
	int				n;
	struct s_files	*next;
}					t_files;

/*
**	li_00 initialisation
*/

void			ft_init_elem(t_all *elem);
int				ft_read(t_all *elem);
void			ft_print_infos(t_all *elem);

/*
**	li_01 Parse Tools
*/

void			ft_status_update(t_all *elem, t_room *tmp);
int				ft_room(t_all *elem, char **tab_coor);
int				ft_one_line_tube_or_room(t_all *elem, char *line);
int				ft_get_instructions(t_all *elem, char *line);



/*
**	li_01bis Parse Tools 
*/

int				ft_realloc_room_tab(t_room ***tab, t_room *room);
int				ft_tube_aux(t_all *elem, t_room **tmp, t_room **cur);
int				ft_tube(t_all *elem, char *line);
int				ft_check_nb(char *s, int *nb);
int				ft_check_nb_ants(t_all *elem, char *str, int *i);

/*
**	li_02 begin
*/

void			ft_save_map(t_all *elem, char *line);
void			push_file(t_files **files, t_room *room, t_path *path);
t_files			*pop_file(t_files **file);
void			add_path_to_tab(t_tab_path **tab, t_path *path);
void			free_file(t_files *file);

/*
**	li_03 Algo
*/

t_tab_path		*edmond_karp(t_all *elem, t_room ***matrice, int **matrice_flow, t_room *start);

/*
**	li_09a Free and error
*/

void			ft_free_room(t_lst *lst);
void			free_room(t_room *room);
void			ft_free_lst(t_lst *lst, void (*f)(t_lst *lst));
void			ft_free_all(t_all *elem);
int				ft_free_them(size_t n, ...);
int				ft_error_tube(char ***tab_tube);
void			ft_error(int nb);
void			ft_free_path(t_lst *lst);

/*
**	li_09b Search and Init Tools
*/

t_room			*ft_init_start(t_all *elem);
t_room			*ft_init_end(t_all *elem);
void			ft_set_matrice(t_room **tmp, t_room **cur, t_room ***matrice);
t_room			***ft_init_matrice(int number_rooms);
void			ft_find_room(t_room **tmp, char *room);


/*
**	li_09c Matrice Tools
*/


t_room			***matrice_cpy(t_all elem, t_room ***matrice);
void			ft_free_matrice(t_room ***matrice);
void			ft_free_matrice_flow(int **matrice);
int				**create_matrice_flow(t_all elem);
int				**matrice_flow_cpy(t_all elem, int **matrice);



/*
**	li_09d Path Tools
*/

void			add_path(t_path **path, t_room *room);
t_path			*path_cpy(t_path *path);
int 			compare_path(t_path *path1, t_path *path2);
int				is_not_in_path(t_path *path, t_room *room);
int 			path_size(t_path *path);

/*
**	li_06_tab_path_tools
*/

void			free_tab_path(t_tab_path *tab);
void			free_path(t_path *path);
t_tab_path		*remove_bad_path(t_tab_path *tab);
int				tab_size(t_tab_path *tab);

/*
**	li_05 dipatch
*/

void	ft_dispatch(t_all elem, t_tab_path *tab);


/*
**	debbug
*/

void	ft_print_matrice_flow(int **matrice, t_all *elem);
void	ft_print_matrice(t_room ***matrice, t_all *elem);
void	ft_print_matrice_weight(t_room ***matrice, t_all *elem);
void	print_path(t_path *path);
void	print_tab_path(t_tab_path *tab);
void	print_path(t_path *path);
void	print_tab_path(t_tab_path *tab);

#endif

/*

la room start est linked to start a 0 (par defaut -1), la room end est llinked to end a 0
On etudie tous les liens d abord au premier tour start puis end puis start puis end etc...
on set limited factor avec le plus petit des deux mouvements
// puis de ces x chemins, chaque fois que path is dead on applique -1


*/
