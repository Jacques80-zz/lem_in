/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:50:29 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:31:28 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <locale.h>
# define UL unsigned long
# define ULL unsigned long long
# include "libft.h"


/*
**	La fonction printf est prototypee de la maniere suivante:
**	% [drapeaux] [largeur] [.precision] [modification] type.
**
**	Les drapeaux se trouvent dans la struct s_flag
**	Elle contient les informations suivantes:
**	'-' = left = alignement a gauche pour la largeur donnee
**	' ' = blank = insertion d'un space si la valeur numerique est > 0
**	'+' = plus = affichage forcé du sgne de la valeur numerique
**	'0' = zero = ajout de '0' si la valeur est + courte que le display demandé
**	''' = apos = ajoute des separateurs entre les milliers (non gere)
**	'#' = hash = ajoute le prefixe 0, ou 0x ou 0X pour o, x, et X
**				 force l'affichage du point decimal pour e, E et f
**				 force l'affichage du point decimal pr g et G sans del les '0'
*/

typedef	struct		s_flag
{
	int				left;
	int				blank;
	int				plus;
	int				zero;
	int				apos;
	int				hash;
}					t_flag;

/*
**	La struct s_chain est cree a chaque noeud '%' et en l'absence de celui ci
**	C'est la seule liste chainée de cet exercice
**	Elle contient les infomations suivantes:
**	la struct s_flag (cf plus haut)
**	un int just show qui est utile quand on ne rencontre pas de noeud '%'
**	width = qui correspond a la largeur de sortie souhaitée
**	nbr_carac = qui correspond au nombre de caractere de l'element de base
**	nbr_byte = qui differe de nbr_carac pour 'C' ou 'S' par exemple
**	give_p = qui est a 1 si une precision est definie, utile si prec = 0
**	len = qui est un mirroir de char c dans s_len, qui definit une conv de type
**	conv= un mirroir de char c ds s_conv,il apl le pt sur ft correspondt
**	maj est un int qui indique que la sortie doit etre en uppercase ('O' p.e.)
**	cnull qui indique que l'element est null (par defaut a 1 si NULL a 0)
**	*f un pt sur fonction issu de la struct t_conv
**	show qui est un tableau de char qui sera modifié au cours de la ft
**	next qui est un pt vers le prochain element (maillon) de la liste
*/

typedef struct		s_chain
{
	t_flag			*flag;
	int				just_show;
	size_t			width;
	size_t			nbr_carac;
	size_t			nbr_byte;
	int				give_p;
	size_t			prec;
	char			len;
	char			conv;
	int				maj;
	char			cnull;
	int				(*f)(struct s_chain *, va_list ap);
	char			*show;
	struct s_chain	*next;
}					t_chain;

/*
**	La struct s_len contient le conversion de type
**	un char unique pour qui appelera un cast
**	un tableau de char qui permettra de comparer avec ft_match
**	un int donnant le nombre de caracteres de ce tableau
**	hh = H = (d, i) signed char, (u,o,x,X) unsigned int
**	h = h = (d, i) short int, (u,o,x,X) unsigned short int
**	ll = L = (d,i) long long int, (u,o,x,X) unsigned long int
**	l = l = (d, i) long int, (u,o,x,X) u long int, (c) wint_t, (s) wchar_t*
**	j = j = (d,i) intmax_t, (u,o,x,X) uintmax_t
**	z = z = (d,i) size_t, (u,o,x,X) size_t
*/

typedef struct		s_len
{
	char			c;
	char			*len;
	int				i;
}					t_len;

static	t_len		g_len[] =
{
	{'H', "hh*", 2},
	{'h', "h*", 1},
	{'m', "ll*", 2},
	{'l', "l*", 1},
	{'L', "L*", 1},
	{'j', "j*", 1},
	{'z', "z*", 1},
	{'\0', NULL, 0}
};

int					ft_printf(const char *restrict format, ...);
int					ft_show_only_parser(const char *format,
		size_t len, t_chain **chain);
const char			*ft_parser(const char *format,
		t_chain *elem, t_chain **chain);
/*
** FONCTIONS DE PARSING
*/
int					ft_find_flag(char c, t_chain *elem);
const char			*ft_find_width(const char *format, t_chain *elem);
const char			*ft_find_precision(const char *format, t_chain *elem);
const char			*ft_find_length(const char *format, t_chain *elem);
int					ft_is_conv(char c, t_chain *elem);
/*
** FONCTIONS DE TRAITEMENT
*/
int					ft_handler(va_list ap, t_chain *chain);
int					ft_int_handler(t_chain *elem, va_list ap);
int					ft_error_handler(t_chain *elem, va_list ap);
int					ft_uint_handler(t_chain *elem, va_list ap);
int					ft_str_handler(t_chain *elem, va_list ap);
int					ft_str_w_handler(t_chain *elem, va_list ap);
char				*ft_one_byte(wchar_t wc);
char				*ft_four_bytes(wchar_t wc);
char				*ft_three_bytes(wchar_t wc);
char				*ft_two_bytes(wchar_t wc);
int					ft_percent_handler(t_chain *elem, va_list ap);
int					ft_null_w_char(t_chain *elem);
char				*ft_prec_on_w(t_chain *elem);
int					ft_show_all(t_chain *elem);
int					ft_show_error(t_chain *elem, t_chain *begin);
t_chain				*ft_lstfree(t_chain *current);
int					ft_roman_handler(t_chain *elem, va_list ap);
int					ft_binary_handler(t_chain *elem, va_list ap);
/*
**	FONCTIONS QUI GERENT LES DIFFERENTS FLAGS
*/
char				*ft_plus(t_chain *elem, char c);
char				*ft_precision(t_chain *elem);
char				*ft_width(t_chain *elem, t_flag *flag);
char				*ft_maj(t_chain *elem);
char				*ft_0x_hexa(char *show, char c, t_chain *elem);
char				*ft_0_octal(char *show);
char				*ft_hash(t_chain *elem);
int					ft_str_modifier(t_chain *elem, t_flag *flag);
/*
** FONCTIONS UTILES POUR LISTES CHAINEES
*/
t_chain				*ft_create_elem(void);
void				ft_init_chain_info(t_chain *elem, t_flag *flag);
void				ft_lstadd_after(t_chain *elem, t_chain **chain);
t_chain				*ft_get_dollar_order(t_chain *chain);
/*
** FONCTIONS UTILES QUI SERAIENT TOUTES DANS RECOGNIZE SI PAS DE NORME
*/
int					ft_is_decimal(char b);
int					ft_is_integer(char b);
char				*ft_start_digit(char *str, t_chain *elem);
int					ft_get_base(char c);
int					ft_need_toupper(char c);
int					ft_is_w_char(t_chain *elem);

/*
**	La struct s_conv contient le type de conversion (et non la conv de type)
**	souhaitée elle contient un char, et un pointeur sur fonction correspondant
*/

typedef	struct		s_conv
{
	char			conv;
	int				(*f)(t_chain *, va_list ap);
}					t_conv;

static t_conv	g_conv[] =
{
	{'d', &ft_int_handler},
	{'D', &ft_int_handler},
	{'i', &ft_int_handler},
	{'B', &ft_roman_handler},
	{'b', &ft_binary_handler},
	{'u', &ft_uint_handler},
	{'U', &ft_uint_handler},
	{'o', &ft_uint_handler},
	{'O', &ft_uint_handler},
	{'x', &ft_uint_handler},
	{'X', &ft_uint_handler},
	{'s', &ft_str_handler},
	{'S', &ft_str_w_handler},
	{'c', &ft_str_handler},
	{'C', &ft_str_w_handler},
	{'p', &ft_uint_handler},
	{'%', &ft_percent_handler},
	{0, NULL}
};

#endif
