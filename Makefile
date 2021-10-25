# COLORS

GREEN	= \033[0;32m
RED		= \033[0;31m
BLUE	= \033[0;34m
GREY	= \033[38;5;240m
WHITE	= \033[0;37m
QUIT	= \033[0m

# MACROS

NAME	=	minishell
SRCS	=	$(wildcard src/*.c)
DIR_O	=	obj/
OBJS	=	$(SRCS:src/%.c=obj/%.o)
DOTH	=	extras/includes
LIBFT	=	extras/libft
INCL	=	extras/includes/minishell.h
DBINCL	=	extras/42_memleak_check/malloc_leak_checker.h
CC		=	gcc
#UPDATE READLINE via brew because the Mac one is too old
CFLAGS	=	-Wall -Wextra -Werror `pkg-config readline --cflags`
DBFLAGS =	-g -fsanitize=address -lmlc -Lextras/42_memleak_check
INCLUDE	=	-I./$(DOTH) -I./$(LIBFT) `pkg-config readline --cflags`
LINKS	=	-L./$(LIBFT) -lft `pkg-config readline --libs`

# RULES

all:	$(NAME)

$(NAME): libcheck libft $(INCL) $(DIR_O) $(OBJS)
	@printf "$(GREEN)]$(QUIT)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LINKS)
	@echo "\n$(GREEN)\n"
	@echo "$(NAME) executable CREATED"
	@echo "\n$(QUIT)\n"

$(DIR_O)%.o: src/%.c
	@$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@
	@printf "$(GREEN)#$(QUIT)"

$(OBJS):	| $(DIR_O)

$(DIR_O):
	@mkdir -p $(DIR_O)

libcheck:
	@bash scripts/lib_setup.sh
	@echo

debug:	libcheck libft $(INCL) $(DIR_O) $(OBJS)
	@printf "$(GREEN)]$(QUIT)"
	@$(CC) $(CFLAGS) $(DBFLAGS) $(wildcard src/*.c) $(wildcard extras/libft/src/*c) -o $(NAME) $(LINKS)
	@echo "\n$(GREEN)\n"
	@echo "$(NAME) debug executable CREATED"
	@echo "\n$(QUIT)\n"

libft:
	@echo "$(WHITE) [ .. ] Creating LIBFT [ .. ]$(GREEN)"
	@make -C $(LIBFT)
	@echo "\n$(GREEN)\n"
	@echo "LIBFT library CREATED"
	@printf "$(WHITE) \n\n[ .. ] Creating '$(NAME)' [ .. ]$(QUIT)\n\n$(GREEN)["

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
