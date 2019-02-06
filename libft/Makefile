# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/30 10:34:30 by jdouniol          #+#    #+#              #
#    Updated: 2019/02/05 16:01:24 by fallouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC			=	gcc
FLAGS		= 	-Wall -Werror -Wextra

_SRC 		= 	basic_print.c \
				buffer.c \
				conv_d.c \
				ft_aux.c \
				ft_lltoa.c \
				ft_print.c \
				ft_printf.c \
				ft_putfloat.c \
				parsing.c

_LSRC 		=	ft_putchar.c ft_putstr.c ft_memset.c ft_bzero.c ft_memcpy.c \
				ft_memccpy.c ft_strlen.c ft_strdup.c ft_tolower.c \
				ft_toupper.c ft_isprint.c ft_isascii.c ft_isalnum.c \
				ft_isdigit.c ft_isalpha.c ft_atoi.c ft_strncmp.c ft_strcmp.c \
				ft_strstr.c ft_strnstr.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	  			ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c \
	  			ft_strlcat.c ft_strchr.c ft_strrchr.c ft_memalloc.c \
	  			ft_memdel.c ft_strnew.c ft_strclr.c ft_striter.c \
	  			ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
	  			ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
	  			ft_strsplit.c ft_itoa.c ft_putendl.c ft_putnbr.c \
	  			ft_putnbr_fd.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	  			ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	  			ft_lstiter.c ft_lstmap.c ft_strdel.c ft_lstaddafter.c \
	  			ft_lstswap.c ft_listmerge.c ft_lstlast.c ft_lstsize.c \
	  			ft_itoa_ll.c ft_match.c ft_itoa_base.c ft_itoa_base_ll.c \
	  			ft_strjoin_clr.c ft_atoi_base.c ft_atoi_base_ll.c \
	  			ft_strdupifexist.c ft_strtrim_c.c ft_strtolower.c \
	  			ft_strtoupper.c get_next_line.c ft_split_whitespaces.c \
	  			ft_islower.c ft_isspace.c ft_istrim.c ft_isupper.c \
	  			ft_atol.c ft_isint.c ft_atoll.c ft_to_lower.c ft_lstget.c \
	  			ft_realloc.c \

HEADER		= ../includes/libft.h ../includes/ft_printf.h
PRINTF_DIR	= pf_sources
#LIBFT_DIR	= libft
SRC			= $(addprefix $(PRINTF_DIR)/, $(_SRC))
LSRC		= $(addprefix , $(_LSRC))
BIN 		= $(SRC:.c=.o)
LBIN		= $(LSRC:.c=.o)
BIN			+= $(LBIN)
RM			= /bin/rm

#	all : généralement la première du fichier, elle regroupe dans ces dépendances 
# l'ensemble des exécutables à produire.
all : $(NAME)

$(NAME) : $(BIN) $(HEADER)
	@printf "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@ar rc $(NAME) $(BIN)
	@ranlib $(NAME)

%.o : %.c $(HEADER)
	@printf "\033[1:92mCompiling $(NAME)\033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@$(CC) $(FLAGS) -c $< -o $@ -I ../includes
	@printf "\033[A\033[2K"
# clean : elle permet de supprimer tout les fichiers intermédiaires.
clean :
	@rm -f $(BIN)
	@printf "\033[1:32mCleaning object files -> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"

fclean : clean
	@rm -f $(NAME)
	@printf "\033[1:32mCleaning binary -------> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"

re : 
	@make fclean
	@make
