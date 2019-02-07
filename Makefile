NAME_LEM_IN = lem_in

LEM_IN		=	lem_in

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g #3 -fsanitize=address

_LI_SRCS	= 	li_00_lem_in.c \
			  	li_01_parse_tools.c \
			  	li_01bis_parse_tools.c \
			  	li_02_begin.c \
			  	li_03_algo.c \
			  	li_04_algo_tools.c \
			  	li_09a_free_and_error.c \
			  	li_09b_search_and_init_tools.c

_LIBFT		=	libft.a

SRCS_DIR	=	sources
LIB_DIR		=	libft
LI_SRCS		=	$(addprefix $(SRCS_DIR)/, $(_LI_SRCS))
LIBFT		=	$(addprefix $(LIB_DIR), $(_LIBFT))

LI_OBJS		=	$(LI_SRCS:.c=.o)

all:	$(LEM_IN)

$(LEM_IN) : $(LIBFT) $(LI_OBJS)
	@$(CC) $(CFLAGS) -o $(LEM_IN) $(LI_OBJS) -L$(LIB_DIR) -lft
	@echo "$(LEM_IN) : $(_GREEN)Done$(_END)"

$(LIBFT):
	@make -C $(LIB_DIR)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I includes/

clean:
	@make fclean -C $(LIB_DIR)
	@/bin/rm -f $(LI_OBJS)
	@echo "lem_in clean : $(_GREEN)Done$(_END)"

fclean: clean
	@/bin/rm -f $(LEM_IN)
	@echo "lem_in fclean : $(_GREEN)Done$(_END)"

re:
	@make fclean
	@make

.PHONY: all clean fclean re
