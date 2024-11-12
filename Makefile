# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 16:11:59 by dangonz3          #+#    #+#              #
#    Updated: 2024/11/12 17:10:49 by dangonz3         ###   ########.fr        #
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
	
MLX_DIR = ./MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

all: $(LIBFT_LIB) libmlx $(NAME)
	@echo "$(COLOR_GREEN)------------ PROCESS FINISHED ------------ $(COLOR_RESET)"

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) -o $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR) -s

libmlx:
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && $(MAKE) -C $(MLX_DIR)/build -j4 -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: MLX COMPILED ------------ $(COLOR_RESET)"
# cmake genera un Makefile en el directorio indicado (-B $(MLX_DIR)/build)
	
%.o: %.c
	$(CC) $(CCFLAGS) -c $< $(HEADERS) -o $@
	@echo "$(COLOR_GREEN)------------ MESSAGE: $@ COMPILED ------------ $(COLOR_RESET)"
	
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean -s
	$(MAKE) -C $(MLX_DIR)/build clean -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"
	
fclean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean -s
	$(MAKE) -C $(MLX_DIR)/build clean -s
	$(MAKE) -C $(LIBFT_DIR) fclean -s
	rm -f $(NAME)
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"

re: fclean all

.PHONY:	all, clean, fclean, re, libmlx
