# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: n <n@student.42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 16:16:45 by annmakar          #+#    #+#              #
#    Updated: 2025/05/20 00:24:09 by n                ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        = so_long
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include

SRCS        = so_long.c moves.c

LIBFT_DIR   = libft
FP_DIR      = ft_printf
GNL_DIR     = get_next_line
MLX_DIR     = mlx

CC          = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(FP_DIR) -I$(GNL_DIR) -I.

UNAME_S     := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLX_FLAGS  = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else ifeq ($(UNAME_S), Darwin)
	MLX_FLAGS  = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(FP_DIR)
	$(MAKE) -C $(GNL_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) \
		-L$(LIBFT_DIR) -lft \
		-L$(FP_DIR) -lftprintf \
		$(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FP_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FP_DIR) fclean
	$(MAKE) -C $(GNL_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
