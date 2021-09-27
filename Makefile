# COLORS

GREEN	= \033[0;32m
RED		= \033[0;31m
BLUE	= \033[0;34m
GREY	= \033[38;5;240m
WHITE	= \033[0;37m
QUIT	= \033[0m

# MACROS

NAME	=	minishell
SRCS	=	$(wildcard cfiles/*.c)
DIR_O	=	OBJ/
OBJS	=	$(SRCS:cfiles/%.c=OBJ/%.o)
DOTH	=	extras/hfiles
LIBFT	=	extras/libft
LFT_EXE	=	extras/libft
CC		=	gcc
#UPDATE READLINE via brew because the Mac one is too old
CFLAGS	=	-Wall -Wextra -Werror `pkg-config readline --cflags`
LDFLAGS = 	-g `pkg-config readline --libs` #-fsanitize=address
INCLUDE	=	-I./$(DOTH) -I./$(LIBFT) `pkg-config readline --cflags`
LINKS	=	-L./$(LIBFT) -lft `pkg-config readline --libs`

# RULES

all:	$(NAME)

$(NAME): libcheck libft $(DIR_O) $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(wildcard cfiles/*.c) $(wildcard extras/libft/*c) -o $(NAME) $(LINKS)
	@echo "\n$(GREEN)\n"
	@echo "$(NAME) executable CREATED"
	@echo "\n$(QUIT)\n"

$(DIR_O)%.o: cfiles/%.c
	@$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@
	@echo "$(GREEN)#$(QUIT)\c"

$(OBJS):	| $(DIR_O)

$(DIR_O):
	@mkdir -p $(DIR_O)

libcheck:
	@bash scripts/lib_setup.sh

libft:
	@echo "$(WHITE) [ .. ] Creating LIBFT [ .. ]$(GREEN)"
	@make -C $(LIBFT)
	@echo "\n$(GREEN)\n"
	@echo "LIBFT library CREATED"
	@echo "$(WHITE) \n\n\n[ .. ] Creating '$(NAME)' [ .. ]$(QUIT)"

clean:
	@echo "$(RED) [ .. ] Deleting LIBFT [ .. ]"
	@echo "$(RED)"
	@make -C $(LIBFT) fclean
	@echo "LIBFT DELETED"
	@echo "$(QUIT)"
	@echo "$(RED) [ .. ] Deleting .o files [ .. ]$(QUIT)"
	@rm -fr $(DIR_O)

fclean:	clean
	@echo "$(RED) [ .. ] Deleting '$(NAME)' executable  [ .. ]"
	@rm -fr $(NAME)
	@echo "\n'$(NAME)' executable DELETED"
	@echo "$(QUIT)"

re:		fclean all

.PHONY	=	all clean fclean re
