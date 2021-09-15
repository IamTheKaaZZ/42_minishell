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
DIR_O	=	OBJ
OBJS	=	$(SRCS:%.c=%.o)
DOTH	=	extras/hfiles
LIBFT	=	extras/libft
LFT_EXE	=	extras/libft
CC		=	gcc
#UPDATE READLINE via brew because the Mac one is too old
CFLAGS	=	-Wall -Wextra -Werror `pkg-config readline --cflags`
LDFLAGS = 	-g `pkg-config readline --libs` -fsanitize=address
INCLUDE	=	-I./$(DOTH) -I./$(LIBFT) `pkg-config readline --cflags`
LINKS	=	-L./$(LIBFT) -lft `pkg-config readline --libs`

# RULES

all:	$(NAME)

$(NAME): libft $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(wildcard cfiles/*.c) -o $(NAME) $(LINKS)
	@mkdir -p $(DIR_O)
	@mv cfiles/*.o OBJ
	@echo "\n$(GREEN)\n"
	@cat ./fonts/minishell_created.txt
	@echo "\n$(RESET)\n"

%.o: %.c
	@$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@
	@echo "$(GREEN)#$(RESET)\c"

libft:
	@echo "$(WHITE) [ .. ] Creating LIBFT [ .. ]$(RESET)"
	@make -C $(LIBFT)
	@echo "\n$(GREEN)\n"
	@cat ./fonts/libft_created.txt
	@echo "$(WHITE) \n\n\n[ .. ] Creating '$(NAME)' [ .. ]$(RESET)"

clean:
	@echo "$(RED) [ .. ] Deleting LIBFT [ .. ]"
	@echo "$(RED)"
	@make -C $(LIBFT) fclean
	@cat ./fonts/libft_deleted.txt
	@echo "$(RESET)"
	@echo "$(RED) [ .. ] Deleting .o files [ .. ]$(RESET)"
	@rm -fr $(DIR_O)

fclean:	clean
	@echo "$(RED) [ .. ] Deleting '$(NAME)' executable  [ .. ]$(RESET)"
	@rm -fr $(NAME)
	@cat	./fonts/minishell_deleted.txt
	@echo "$(RESET)"

re:		fclean all

.PHONY	=	all clean fclean re
