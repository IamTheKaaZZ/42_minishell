# PLACE AT THE TOP OF YOUR MAKEFILE
#---------------------------------
# Progress bar defs
#--------------------------------
#  words = count the number of words
ifneq ($(words $(MAKECMDGOALS)),1) # if no argument was given to make...
.DEFAULT_GOAL = all # set the default goal to all
#  http://www.gnu.org/software/make/manual/make.html
#  $@ = target name
#  %: = last resort recipe
#  --no-print-directory = don't print enter/leave messages for each output grouping
#  MAKEFILE_LIST = has a list of all the parsed Makefiles that can be found *.mk, Makefile, etc
#  -n = dry run, just print the recipes
#  -r = no builtin rules, disables implicit rules
#  -R = no builtin variables, disables implicit variables
#  -f = specify the name of the Makefile
%:                   # define a last resort default rule
		@$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST)) # recursive make call,
else
ifndef ECHO
#  execute a dry run of make, defining echo beforehand, and count all the instances of "COUNTTHIS"
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
		-nrRf $(firstword $(MAKEFILE_LIST)) \
		ECHO="COUNTTHIS" | grep -c "COUNTTHIS")
#  eval = evaluate the text and read the results as makefile commands
N := x
#  Recursively expand C for each instance of ECHO to count more x's
C = $(words $N)$(eval N := x $N)
#  Multipy the count of x's by 100, and divide by the count of "COUNTTHIS"
#  Followed by a percent sign
#  And wrap it all in square brackets
ECHO = echo -ne "$(QUIT)\r [`expr $C '*' 100 / $T`%]"
endif
#------------------
# end progress bar
#------------------

# REST OF YOUR MAKEFILE HERE

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
DBFLAGS =	-g -fsanitize=address #-rdynamic -lmlc -Lextras/42_memleak_check
INCLUDE	=	-I./$(DOTH) -I./$(LIBFT) `pkg-config readline --cflags`
LINKS	=	-L./$(LIBFT) -lft `pkg-config readline --libs`

# RULES

all:	$(NAME)

$(NAME):	$(INCL) $(OBJS)
	@$(ECHO) "\n\n$(GREEN)'$(NAME)' objects compiled.$(QUIT)\n\n"
	@bash scripts/lib_setup.sh
	@$(ECHO)
	@make -C $(LIBFT)
	@$(ECHO) "$(WHITE)\n\n [ .. ] Creating '$(NAME)' [ .. ]$(QUIT)\n\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LINKS)
	@$(ECHO) "\n$(GREEN)\n"
	@$(ECHO) "$(NAME) executable CREATED"
	@$(ECHO) "\n$(QUIT)\n"

$(DIR_O)%.o: src/%.c
	@$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@
	@$(ECHO) "$(GREEN)$@$(QUIT)"

$(OBJS):	| $(DIR_O)

$(DIR_O):
	@mkdir -p $(DIR_O)

libcheck:
	@bash scripts/lib_setup.sh
	@$(ECHO)

debug:	libcheck libft $(INCL) $(DIR_O) $(OBJS)
	@printf "\n$(GREEN)]$(QUIT)"
	@$(CC) $(CFLAGS) $(DBFLAGS) $(wildcard src/*.c) $(wildcard extras/libft/src/*c)  -o $(NAME) $(LINKS)
	@$(ECHO) "\n$(GREEN)\n"
	@$(ECHO) "$(NAME) debug executable CREATED"
	@$(ECHO) "\n$(QUIT)\n"

libft:
	@make -C $(LIBFT)

clean:
	@$(ECHO) "$(RED) [ .. ] Deleting LIBFT [ .. ]"
	@$(ECHO) "$(RED)"
	@make -C $(LIBFT) fclean
	@$(ECHO) "LIBFT DELETED"
	@$(ECHO) "$(QUIT)"
	@$(ECHO) "$(RED) [ .. ] Deleting .o files [ .. ]$(QUIT)"
	@rm -fr $(DIR_O)

fclean:	clean
	@$(ECHO) "$(RED) [ .. ] Deleting '$(NAME)' executable  [ .. ]"
	@rm -fr $(NAME) *.dSYM
	@$(ECHO) "'$(NAME)' executable DELETED"
	@$(ECHO) "$(QUIT)"

re:		fclean all

.PHONY	=	all clean fclean re

#----- Progressbar endif at end Makefile
endif
