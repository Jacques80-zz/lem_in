/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:46:42 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:31:38 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include "ft_printf.h"
# define GNL_ERROR		-1
# define GNL_END		0
# define GNL_LINE_READ	1
# define GNL_BUFF_SIZE 4096
# define ABS(Value) (Value < 0 ? -Value : Value)
# define MAX_INT_POS 2147483647
# define MAX_INT_NEG -2147483648
# define ULL unsigned long long
# define UL unsigned long

typedef unsigned char	t_byte;

typedef struct			s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}						t_list;

void					*ft_memset(void *b, int c, size_t len);
size_t					ft_strlen(const char *str);
char					*ft_strdup(const char *strsrc);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strncpy(char *dest, const char *src, size_t n);
char					*ft_strcat(char *dest, const char *src);
char					*ft_strncat(char *dest, const char *src, size_t n);
int						ft_tolower(int c);
int						ft_toupper(int c);
int						ft_atoi(const char *str);
int						ft_atoi_base(const char *str, unsigned int from);
UL						ft_atoi_base_ll(const char *str, unsigned int from);
char					*ft_strstr(const char *src, const char *to_find);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isprint(int c);
int						ft_isascii(int c);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c,
							size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strnstr(const char *src, const char *to_find,
							size_t n);
void					*ft_memmove(void *s1, const void *s2, size_t n);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
void					ft_putchar(char c);
void					*ft_memalloc(size_t size);
void					ft_putstr(char const *s);
void					ft_putnbr(int nb);
void					ft_putchar_fd(char c, int fd);
void					ft_putnbr_fd(int nb, int fd);
void					ft_putstr_fd(char const *s, int fd);
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
void					ft_strclr(char *s);
char					*ft_strnew(size_t size);
void					ft_putendl(char const *s);
void					ft_putendl_fd(char const *s, int fd);
void					ft_memdel(void **ap);
void					ft_strdel(char **as);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
							char));
char					*ft_strsub(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
char					*ft_strtrim_c(char const *s, char c);
char					**ft_strsplit(char const *s, char c);
char					*ft_strjoin_clr(char *s1, char *s2);
char					*ft_strdupifexist(const char *str);
char					*ft_itoa(int i);
char					*ft_itoa_ll(long long n);
char					*ft_itoa_base(unsigned int value, unsigned int base);
char					*ft_itoa_base_ll(ULL value, unsigned int base);
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst, void (*del)(void *,
							size_t));
void					ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void					ft_lstadd(t_list **alist, t_list *nlst);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list					*ft_lstswap(t_list *a, t_list *b);
int						ft_lstsize(t_list *begin_list);
t_list					*ft_lstlast(t_list *begin_list);
void					ft_lstaddafter(t_list **alst, t_list **neww);
void					ft_listmerge(t_list **begin_list1, t_list *begin_list2);
int						ft_islower(int c);
int						ft_isupper(int c);
int						ft_isspace(int c);
char					*ft_strtoupper(char *str);
char					*ft_strtolower(char *str);
char					**ft_split_whitespaces(char *str);
int						ft_istrim(int c);
int						get_next_line(int const fd, char **line);
int						ft_match(const char *s1, const char *s2);
long long				ft_atol(const char *nptr);
int 					ft_isint(long long nbr);

#endif
