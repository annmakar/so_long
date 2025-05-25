# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: annmakar <annmakar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 17:44:23 by annmakar          #+#    #+#              #
#    Updated: 2025/05/25 17:59:31 by annmakar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_strlen.c ft_putstr_fd.c

OBJS = $(SRCS:.c=.o)

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -fPIC

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)

	ar rcs $(NAME) $(OBJS)

%.o:%.c

	$(CC) $(CFLAGS) -I. -c $? -o $@

clean:

	$(RM) $(OBJS)
	$(RM) libft.so

fclean:	clean

	$(RM) $(NAME)

re:	fclean $(NAME)

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)

.PHONY: all clean fclean re