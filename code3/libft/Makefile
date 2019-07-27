# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oouklich <ouklichoussama@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/19 18:21:45 by oouklich          #+#    #+#              #
#    Updated: 2019/07/10 15:46:15 by oouklich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_putchar.c ft_striteri.c ft_striter.c
SRC += ft_atoi.c ft_putchar_fd.c ft_strjoin.c
SRC += ft_bzero.c ft_putendl.c ft_strlcat.c
SRC += ft_countword.c ft_putendl_fd.c ft_strlen.c
SRC += ft_isalnum.c ft_putnbr.c ft_strlowcase.c
SRC += ft_isalpha.c ft_putnbr_fd.c ft_strmap.c
SRC += ft_isascii.c ft_putstr.c ft_strmapi.c
SRC += ft_isdigit.c ft_putstr_fd.c ft_strncat.c
SRC += ft_isprint.c ft_sort_params.c ft_strncmp.c
SRC += ft_itoa.c ft_str_is_alpha.c ft_strncpy.c
SRC += ft_lstadd.c ft_str_is_lowercase.c ft_strnequ.c
SRC += ft_lstdel.c ft_str_is_numeric.c ft_strnew.c
SRC += ft_lstdelone.c ft_str_is_printable.c ft_strnstr.c
SRC += ft_lstiter.c ft_str_is_uppercase.c ft_strrchr.c
SRC += ft_lstmap.c ft_strcapitalize.c ft_strsplit.c
SRC += ft_lstnew.c ft_strcat.c ft_strstr.c
SRC += ft_memalloc.c ft_strchr.c ft_strsub.c
SRC += ft_memccpy.c ft_strclr.c ft_strtrim.c
SRC += ft_memchr.c ft_strcmp.c ft_strupcase.c
SRC += ft_memcmp.c ft_strcpy.c ft_tolower.c
SRC += ft_memcpy.c ft_strdel.c ft_toupper.c
SRC += ft_memdel.c ft_strdup.c get_next_line.c
SRC += ft_memmove.c ft_strequ.c ft_memset.c

OBJ = ft_putchar.o ft_striteri.o ft_striter.o
OBJ += ft_atoi.o ft_putchar_fd.o ft_strjoin.o
OBJ += ft_bzero.o ft_putendl.o ft_strlcat.o
OBJ += ft_countword.o ft_putendl_fd.o ft_strlen.o
OBJ += ft_isalnum.o ft_putnbr.o ft_strlowcase.o
OBJ += ft_isalpha.o ft_putnbr_fd.o ft_strmap.o
OBJ += ft_isascii.o ft_putstr.o ft_strmapi.o
OBJ += ft_isdigit.o ft_putstr_fd.o ft_strncat.o
OBJ += ft_isprint.o ft_sort_params.o ft_strncmp.o
OBJ += ft_itoa.o ft_str_is_alpha.o ft_strncpy.o
OBJ += ft_lstadd.o ft_str_is_lowercase.o ft_strnequ.o
OBJ += ft_lstdel.o ft_str_is_numeric.o ft_strnew.o
OBJ += ft_lstdelone.o ft_str_is_printable.o ft_strnstr.o
OBJ += ft_lstiter.o ft_str_is_uppercase.o ft_strrchr.o
OBJ += ft_lstmap.o ft_strcapitalize.o ft_strsplit.o
OBJ += ft_lstnew.o ft_strcat.o ft_strstr.o
OBJ += ft_memalloc.o ft_strchr.o ft_strsub.o
OBJ += ft_memccpy.o ft_strclr.o ft_strtrim.o
OBJ += ft_memchr.o ft_strcmp.o ft_strupcase.o
OBJ += ft_memcmp.o ft_strcpy.o ft_tolower.o
OBJ += ft_memcpy.o ft_strdel.o ft_toupper.o
OBJ += ft_memdel.o ft_strdup.o get_next_line.o
OBJ += ft_memmove.o ft_strequ.o ft_memset.o

NAME = libft.a

all: $(NAME)

$(NAME):
	@gcc -c -Wall -Wextra -Werror $(SRC) -I .
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
