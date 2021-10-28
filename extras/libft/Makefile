# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/08 10:32:48 by bcosters          #+#    #+#              #
#    Updated: 2021/10/28 16:06:10 by bcosters         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- MakeFile for LIBFT -*-

# -*- Variable definitions -*-

#	Project sources/objects/headers

SRCS	= ${shell find src -type f \( -name "ft_*.c" ! -name "ft_lst*.c" ! -name "*bonus.c" \)}

SRCS_BONUS = ${shell find src -type f \( -name "ft_*.c" ! -name "*bonus.c" \)}

OBJS	= ${SRCS:src/%.c=obj/%.o}

OBJS_BONUS = ${SRCS_BONUS:src/%.c=obj/%.o}

HEADER	= libft.h

NAME	= libft.a

CC		= gcc

CFLAGS 	= -Wall -Wextra -Werror

#	Own sources/objects/headers

SRCS_OWN = ${wildcard src/*.c}

OBJS_OWN = ${SRCS_OWN:src/%.c=obj/%.o}

HEADERS_OWN = libft.h libft_bonus.h

OBJDIR = obj/

# COLORS

GREEN	= \033[0;32m
RED		= \033[0;31m
BLUE	= \033[0;34m
GREY	= \033[38;5;240m
WHITE	= \033[0;37m
QUIT	= \033[0m

# -*- Rules -*-
#target: dependencies
#	action

#	Implicit rules

${OBJDIR}%.o : src/%.c
			@printf "$(GREEN)#$(QUIT)"
			@$(CC) -c $(CFLAGS) $< -o $@

#	Normal rules

all:		$(NAME)

mand:		fclean $(OBJDIR) $(OBJS) $(HEADER)
			@echo Compiling MANDATORY LIBFT
			@ar rcs $(NAME) $(OBJS)
			@echo FINISHED: Compiling MANDATORY LIBFT

bonus:		fclean $(OBJDIR) $(OBJS_BONUS) $(HEADER)
			@echo Compiling MANDATORY AND BONUS LIBFT
			@ar rcs $(NAME) $(OBJS_BONUS)
			@echo FINISHED: Compiling MANDATORY AND BONUS LIBFT

$(NAME):	$(OBJDIR) ${OBJS_OWN} ${HEADERS_OWN}
			@printf "\n\n$(GREEN)LIBFT objects compiled.$(QUIT)\n"
			@printf "\n\n$(WHITE) [ .. ] Creating LIBFT library [ .. ]$(GREEN)\n"
			@ar rcs ${NAME} ${OBJS_OWN}
			@echo "\n$(GREEN)\n"
			@echo "LIBFT library CREATED"


$(OBJS):		| $(OBJDIR)
$(OBJS_BONUS):	| $(OBJDIR)
$(OBJS_OWN):	| $(OBJDIR)

$(OBJDIR):
			@mkdir -p $(OBJDIR)

.PHONY:		clean

clean:
			@echo Removing object files...
			@rm -rf ${OBJDIR}

fclean:		clean
			@echo Removing library file...
			@rm -f ${NAME}

re:			fclean all