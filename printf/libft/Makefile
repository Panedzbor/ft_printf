# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 16:13:54 by earutiun          #+#    #+#              #
#    Updated: 2024/11/20 18:23:15 by earutiun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# target
NAME = libft.a

# complier and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I.
TFLAGS = -g -Wall -Wextra -I.

# files
SOURCES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRC_BON = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJECTS = $(SOURCES:%.c=%.o)
OBJ_BON = $(SRC_BON:%.c=%.o)

# rules
all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OBJ_BON)

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean bonus

bonus: $(OBJECTS) $(OBJ_BON)
	ar rcs $(NAME) $(OBJECTS) $(OBJ_BON)

test:
	$(CC) $(TFLAGS) ../test_codes/main.c -L. -lft -lbsd
	./a.out
	
.PHONY: all clean fclean re bonus test


