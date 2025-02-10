# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 14:11:54 by earutiun          #+#    #+#              #
#    Updated: 2025/01/10 14:12:15 by earutiun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# target
NAME = libftprintf.a

# complier and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror $(IFLAGS)
TFLAGS = -g -Wall -Wextra $(IFLAGS)
IFLAGS = -I. -Ilibft/
LFLAGS = -L. -Llibft/

# files
#SOURCES = ft_printf.c
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)

LIBFT = ./libft/libft.a

# rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

#%.o: %.c libftprintf.h
#	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.c libftprintf.h
ifeq ($(MAKECMDGOALS),test)
	$(CC) $(TFLAGS) -c $< -o $@
else
	$(CC) $(CFLAGS) -c $< -o $@
endif

clean:
	rm -f $(OBJECTS)
	$(MAKE) clean -C ./libft

fclean: clean
	rm -f $(NAME)
	rm -f a.out
	$(MAKE) fclean -C ./libft

re: fclean all

test: re
	$(CC) -g $(IFLAGS) $(LFLAGS) ../main_test.c -lftprintf -lft
#	$(CC) -g -m64 $(IFLAGS) ../main_test.c -L. -Llibft -lftprintf -lft -o ../main_test.exe
#	./a.out > output.txt
	./a.out
	
.PHONY: all clean fclean re test











