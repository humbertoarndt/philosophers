# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 11:00:48 by harndt            #+#    #+#              #
#    Updated: 2023/01/23 11:20:27 by harndt           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo
CC			:=	cc
CFLAGS		:=	-pthread #-Wall -Werror -Wextra 
HEADERS		:=	includes
SRCS		:=	sources/philo.c	utils/ft_atoi.c	utils/ft_isdigit.c	\
				utils/ft_isnum.c

OBJS		:=	$(SRCS:.c=.o)

GREEN		:= \033[1;32m
RED			:= \033[1;31m
WHT			:= \033[1;37m
EOC			:= \033[1;0m

all:		$(NAME)

%.o:		%.c
			@$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(NAME):	$(OBJS)
			@echo "$(WHT)Compiling PHILOSOPHERS...$(EOC)"
			@$(CC) $(OBJS) -o $@
			@echo "$(GREEN)PHILOSOPHERS build completed.$(EOC)"

clean:
			@echo "$(WHT)Removing .o files...$(EOC)"
			@rm -f $(OBJS)
			@echo "$(GREEN)Clean done.$(EOC)"

fclean:		clean
			@echo "$(WHT)Removing object- and binary -files...$(EOC)"
			@rm -f $(NAME)
			@echo "$(GREEN)Fclean done.$(EOC)"

re:			fclean all

.PHONY:		all clean fclean re