# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 16:11:59 by dangonz3          #+#    #+#              #
#    Updated: 2025/02/06 16:05:20 by dangonz3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			cub3D
NAME_BONUS =	cub3D_bonus
CC =			gcc
CCFLAGS =		-Wall -Wextra -Werror -g

COLOR_GREEN =	\033[0;32m
COLOR_RESET =	\033[0m

SRC_DIR =		./sources
OBJ_DIR =		./obj
SRC_DIR_BONUS =	./sources_bonus
OBJ_DIR_BONUS =	./obj_bonus
INC_DIR =		./include

SRC = $(shell find $(SRC_DIR) -iname "*.c")
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRC_BONUS = $(shell find $(SRC_DIR_BONUS) -iname "*.c")
OBJ_BONUS = $(SRC_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

HEADERS = -I$(INC_DIR) -I$(MLX_DIR)/include

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
	
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

all: $(NAME)
	@echo "$(COLOR_GREEN)------------ PROCESS FINISHED ------------ $(COLOR_RESET)"

$(NAME): $(OBJ) libmlx $(LIBFT_LIB)
	$(CC) $(OBJ) $(MLX_LIB) $(MLX_FLAGS) $(LIBFT_LIB) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $(HEADERS) -c $< -o $@
	@echo "$(COLOR_GREEN)------------ MESSAGE: $@ COMPILED ------------ $(COLOR_RESET)"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) libmlx $(LIBFT_LIB)
	$(CC) $(OBJ_BONUS) $(MLX_LIB) $(MLX_FLAGS) $(LIBFT_LIB) -o $(NAME_BONUS)

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $(HEADERS) -c $< -o $@
	@echo "$(COLOR_GREEN)------------ MESSAGE: $@ COMPILED ------------ $(COLOR_RESET)"

libmlx:
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && $(MAKE) -C $(MLX_DIR)/build -j4 -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: MLX COMPILED ------------ $(COLOR_RESET)"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) -s

clean:
	@rm -fr $(OBJ_DIR)
	@rm -fr $(OBJ_DIR_BONUS)
	@make -C $(LIBFT_DIR) clean -s
	@rm -rf $(MLX_DIR)/build
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"
	
fclean:
	@rm -fr $(OBJ_DIR)
	@rm -fr $(OBJ_DIR_BONUS)
	@make -C $(LIBFT_DIR) fclean -s
	@rm -rf $(MLX_DIR)/build
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "$(COLOR_GREEN)------------ MESSAGE: FCLEANING COMPLETED ------------ $(COLOR_RESET)"

re: fclean all

rebonus: fclean bonus

.PHONY:	all, clean, fclean, re, libmlx
