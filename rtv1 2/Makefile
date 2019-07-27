# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oouklich <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/18 14:32:27 by oouklich          #+#    #+#              #
#    Updated: 2019/07/12 21:16:22 by mel-jadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRCS = *.c

INCLUDES = ./minilibx_macos

FLAGS= -Wall -Wextra -Werror

LIBRARIES = ./minilibx -lmlx -framework OpenGL -framework AppKit

LIBFT = ./libft/ -lft

all: $(NAME)
$(NAME):
	@make -C libft
	@gcc $(FLAGS) -o $(NAME) $(SRCS) -I $(INCLUDES) -L $(LIBRARIES) -L $(LIBFT)

clean:
	@make clean -C libft

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all
