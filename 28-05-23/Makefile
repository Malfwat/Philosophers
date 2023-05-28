# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/27 09:33:56 by malfwa            #+#    #+#              #
#    Updated: 2023/05/28 22:43:17 by amouflet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_DIR	=	srcs/

SRCS	=	$(SRCS_DIR)action.c \
			$(SRCS_DIR)ft_calloc.c \
			$(SRCS_DIR)main.c \
			$(SRCS_DIR)cutlery.c \
			$(SRCS_DIR)my_print.c \
			$(SRCS_DIR)parse_params.c \
			$(SRCS_DIR)simulation.c \
			$(SRCS_DIR)table.c \
			$(SRCS_DIR)time.c \
			$(SRCS_DIR)utils.c

CFLAGS	=	-Wall -Wextra -Werror -g3 -MMD -MP 

CC		=	cc

OBJS_DIR	=	.build/

OBJS	=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS	=	$(OBJS:.o=.d)

DIRS	=	.build/srcs

INCLUDES	= -I./includes

all:	$(NAME)

$(DIRS):
	@mkdir -p $@

$(OBJS_DIR)%.o:	%.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(DIRS) $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -fr .build

fclean:	clean
	rm -rf $(NAME)

re: fclean all 

.PHONY: re clean all fclean 

-include $(DEPS)