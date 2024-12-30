# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 16:11:59 by dangonz3          #+#    #+#              #
#    Updated: 2024/12/30 20:52:03 by dangonz3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CCFLAGS = -Wall -Wextra -Werror

COLOR_GREEN = \033[0;32m
COLOR_RESET = \033[0m

SRC_DIR = sources/
SRC = $(shell find ./$(SRC_DIR) -iname "*.c")
OBJ = $(SRC:.c=.o)

HEADERS = -I ./include -I $(MLX_DIR)/include

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
	
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a 
MLX_FLAGS = -L $(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

all: $(NAME)
	@echo "$(COLOR_GREEN)------------ PROCESS FINISHED ------------ $(COLOR_RESET)"

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(OBJ) $(MLX_LIB) $(MLX_FLAGS) $(LIBFT_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< $(HEADERS) -o $@
	@echo "$(COLOR_GREEN)------------ MESSAGE: $@ COMPILED ------------ $(COLOR_RESET)"

$(MLX_LIB):
	@make -C $(MLX_DIR) -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: MLX COMPILED ------------ $(COLOR_RESET)"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) -s

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"
	
fclean:
	@rm -f $(OBJ)
	@make -C $(MLX_DIR) clean -s
	@make -C $(LIBFT_DIR) fclean -s
	@rm -f $(NAME)
	@echo "$(COLOR_GREEN)------------ MESSAGE: FCLEANING COMPLETED ------------ $(COLOR_RESET)"

re: fclean all

.PHONY:	all, clean, fclean, re, libmlx
