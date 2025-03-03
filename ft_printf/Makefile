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

# files
SOURCES = ft_printf.c allign.c check_format_str.c compare_chars.c extract_format_val.c format.c format_num.c format_str.c ft_ptoa.c ft_utoa.c \
			ft_xtoa.c inv_helper_funcs.c inv_write_spec.c inv_write_str.c printing_utils.c printing_utils2.c sum_chars.c validate_nums.c \
			utils.c utils2.c \
			./libft/ft_isalpha.c ./libft/ft_isdigit.c ./libft/ft_isalnum.c ./libft/ft_isascii.c ./libft/ft_isprint.c ./libft/ft_strlen.c ./libft/ft_memset.c \
			./libft/ft_bzero.c ./libft/ft_memcpy.c ./libft/ft_memmove.c ./libft/ft_strlcpy.c ./libft/ft_strlcat.c ./libft/ft_toupper.c ./libft/ft_tolower.c \
			./libft/ft_strchr.c ./libft/ft_strrchr.c ./libft/ft_strncmp.c ./libft/ft_memchr.c ./libft/ft_memcmp.c ./libft/ft_strnstr.c \
			./libft/ft_atoi.c ./libft/ft_calloc.c ./libft/ft_strdup.c ./libft/ft_substr.c ./libft/ft_strjoin.c ./libft/ft_strtrim.c ./libft/ft_split.c \
			./libft/ft_itoa.c ./libft/ft_strmapi.c ./libft/ft_striteri.c ./libft/ft_putchar_fd.c ./libft/ft_putstr_fd.c ./libft/ft_putendl_fd.c \
			./libft/ft_putnbr_fd.c ./libft/ft_lstnew_bonus.c ./libft/ft_lstadd_front_bonus.c ./libft/ft_lstsize_bonus.c ./libft/ft_lstlast_bonus.c \
			./libft/ft_lstadd_back_bonus.c ./libft/ft_lstdelone_bonus.c ./libft/ft_lstclear_bonus.c ./libft/ft_lstiter_bonus.c ./libft/ft_lstmap_bonus.c
OBJECTS = $(SOURCES:%.c=%.o)

# rules
all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

%.o: %.c
ifeq ($(MAKECMDGOALS),test)
	$(CC) $(TFLAGS) -c $< -o $@
else
	$(CC) $(CFLAGS) -c $< -o $@
endif

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean all

bonus: all

test: re
	$(CC) $(TFLAGS) -L. ../main_test.c -lftprintf
	norminette -R CheckForbiddenSourceHeader .
	valgrind ./a.out > ../valgrind.txt
#	./a.out

.PHONY: all clean fclean re test bonus











