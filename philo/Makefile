# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 16:24:44 by malfwa            #+#    #+#              #
#    Updated: 2023/03/29 00:16:44 by malfwa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

################################################################################
#                                                                              #
#                                                                              #
#                                  VARIABLES                                   #
#                                                                              #
#                                                                              #
################################################################################

SRC_DIR	=	srcs/

SRCS	=	create_table.c	\
			manage_time.c	\
			ft_atoi.c		\
			simulation.c	\
			utils.c			\
			main.c

OBJ_DIR	=	.build/

OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
	
DEPS	=	$(OBJ:.o=.d)

CC	=	cc

CFLAGS	+=	-Wall -Wextra -Werror -MMD -MP -g3

INC		=	includes/

################################################################################
#                                                                              #
#                                                                              #
#                                    RULES                                     #
#                                                                              #
#                                                                              #
################################################################################


all:	$(NAME)

$(OBJ_DIR):
	@mkdir .build

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I./$(INC)

$(NAME):	Makefile $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all re clean fclean

-include $(DEPS)
