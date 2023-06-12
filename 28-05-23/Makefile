# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 12:02:08 by malfwa            #+#    #+#              #
#    Updated: 2023/06/12 18:34:35 by amouflet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

$(NAME):
	@make -C mandatory

all:	$(NAME) bonus

bonus:
	@make -C bonus_dir
	
clean:
	@make clean -C mandatory/
	@make clean -C bonus/

fclean:
	@make fclean -C mandatory/
	@make fclean -C bonus_dir/
	
clean_bonus:
	@make clean -C bonus_dir/

re: fclean all

.PHONY: all clean fclean clean_bonus fclean_bonus re 