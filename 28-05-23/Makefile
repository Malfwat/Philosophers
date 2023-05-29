# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 12:02:08 by malfwa            #+#    #+#              #
#    Updated: 2023/05/29 13:34:34 by malfwa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

all:	$(NAME)

$(NAME):
	@make -C mandatory

bonus:
	@make -C bonus_dir
	
clean:
	@make clean -C mandatory/

fclean:
	@make fclean -C mandatory/
	@make fclean -C bonus_dir/
	
clean_bonus:
	@make clean -C bonus_dir/

re: fclean all

.PHONY: all clean fclean clean_bonus fclean_bonus re 