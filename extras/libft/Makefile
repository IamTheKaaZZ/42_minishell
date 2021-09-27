# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/08 10:32:48 by bcosters          #+#    #+#              #
#    Updated: 2021/09/10 12:13:36 by bcosters         ###   ########.fr        #
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

# -*- Rules -*-
#target: dependencies
#	action

#	Implicit rules

${OBJDIR}%.o : src/%.c
			@printf "#"
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

$(NAME):	progress $(OBJDIR) ${OBJS_OWN} ${HEADERS_OWN}
			@ar rcs ${NAME} ${OBJS_OWN}
			@echo "]\nFINISHED: Compiling COMPLETE LIBFT (ALL + OWN FUNCTIONS)"

$(OBJS):		| $(OBJDIR)
$(OBJS_BONUS):	| $(OBJDIR)
$(OBJS_OWN):	| $(OBJDIR)

$(OBJDIR):
			mkdir -p $(OBJDIR)

progress:
			@printf "Compiling COMPLETE LIBFT (ALL + OWN FUNCTIONS)\n["


.PHONY:		clean

clean:
			@echo Removing object files...
			@rm -rf ${OBJDIR}

fclean:		clean
			@echo Removing library file...
			@rm -f ${NAME}

re:			fclean all