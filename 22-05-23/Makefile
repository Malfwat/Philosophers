# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/27 09:33:56 by malfwa            #+#    #+#              #
#    Updated: 2023/05/27 09:42:57 by malfwa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_DIR	=	srcs/

SRCS	=	$(SRCS_DIR)action.c \
			$(SRCS_DIR)ft_calloc.c \
			$(SRCS_DIR)ft_putstr.c \
			$(SRCS_DIR)main.c \
			$(SRCS_DIR)my_print.c \
			$(SRCS_DIR)parse_params.c \
			$(SRCS_DIR)simulation.c \
			$(SRCS_DIR)table.c \
			$(SRCS_DIR)time.c \
			$(SRCS_DIR)utils.c

CFLAGS	=	-Wall -Wextra -Werror -g3 $(INCLUDES) 

CC		=	cc

OBJS	=	$(SRCS:.c=.o)

INCLUDES	= -I./includes/

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -fr *.o */*.o

re: clean all 

.PHONY: re clean all 