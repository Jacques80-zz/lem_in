#ifndef LEM_IN_H
# define LEM_IN_H

# define SUCCESS		0
# define ERROR			1
# define FAIL			2
# define PATH_FOUND		3
# define PATH_END		4

# include "libft.h"

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
/*
typedef enum 		e_type
{
	INSTRUCT, COMMENT, NB_ANT, ROOM, PIPE, ERROR
}					t_type;
*/
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
	struct s_room	*prev;
	struct s_room	*next;
	struct s_room	**tab;
	t_status		status;
	t_available		available;

}					t_room; 
/*
typedef struct 		s_path // a creer
{
	int				name_path;
	int				*number_rooms;
	int 			is_dead;
	int 			distance;
	struct s_path 	*next;
}					t_path;
*/ // a voir, nouvelle dans 02.
//utile? 
/*
typedef struct 		s_line
{
	int 			number_line;
	char 			*text;
	char			**split_text;
	int 			number_words; // 1 si int nb fourmi si format nom - nom check nom existe sinon voir comment 2 = si pas comment danger 3 = room = texte space int space int
	t_type			type;
}					t_line;

typedef struct		s_ret_path
{
	t_path			*path;
	int				size;
	int				first_ant; (nb path + modulo nb path)
	int				nb_ant;
	t_path			**room_ant;
	int				step;
}					t_ret_path;

*/
typedef struct				s_path
{
	t_room			*room;
	struct s_path	*prev;
	struct s_path	*next;
}							t_path;

typedef struct				s_tab_path
{
	t_path				*path;
	struct s_tab_path	*next;
}							t_tab_path;

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
	int 			matrice_init;
	int 			all_rooms_are_parsed;
	int				start_id;
	int				end_id;
	int				*tmp_tab_room;
	int				size_tmp_tab_room;		
}					t_all;

typedef struct		s_lst
{
	struct s_lst	*next;
}					t_lst;

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
t_path			*find_path(t_room ***matrice, t_all elem, t_room *start, t_tab_path **tab);


/*
**	li_03 Algo
*/

void			ft_add_weight(t_all elem, t_room ***matrice, int weight, t_room *start);

/*
**	li_04 Algo Tools
*/

t_path			*ft_bfs(t_all *elem, t_room ***matrice, int i_room, t_path *path);

/*
**	li_09a Free and error
*/

void			ft_free_room(t_lst *lst);
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
int				ft_get_start_id(t_all *elem);
int				ft_get_end_id(t_all *elem);
t_room			*ft_get_room_by_id(t_all *elem, int room_id);
void			ft_find_room(t_room **tmp, char *room);

/*
**	li_09c Matrice Tools
*/

void			print_room(t_all elem, int nb);
void			print_all_name(t_all elem);
void			ft_print_matrice(t_room ***matrice, t_all *elem);
void			ft_set_matrice(t_room **tmp, t_room **cur, t_room ***matrice);
t_room			***ft_init_matrice(int number_rooms);
void			ft_print_matrice_weight(t_room ***matrice, t_all *elem);
int 			ft_limited_factor(t_all *elem, t_room ***matrice);


/*
**	li_09d Path Tools
*/

void			empile(t_path **pile, t_room *room);
t_path			*new_elem_path(t_room *room);
void			print_path(t_path *path);
void			print_tab_path(t_tab_path *tab);
void			save_path(t_tab_path **tab, t_path *path);
t_path			*ft_init_path(void);



#endif
/*

la room start est linked to start a 0 (par defaut -1), la room end est llinked to end a 0
On etudie tous les liens d abord au premier tour start puis end puis start puis end etc...
on set limited factor avec le plus petit des deux mouvements
// puis de ces x chemins, chaque fois que path is dead on applique -1


*/
