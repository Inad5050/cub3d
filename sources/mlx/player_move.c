/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:17:26 by dangonz3          #+#    #+#             */
/*   Updated: 2024/12/26 23:40:32 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	player_move(t_cub *c) //filtra el input del jugador para llamar a move()
{
	if (mlx_is_key_down(c->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(c->mlx, MLX_KEY_D))
		return (move(c, 1, 0));
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT) || mlx_is_key_down(c->mlx, MLX_KEY_A))
		return (move(c, -1, 0));
	if (mlx_is_key_down(c->mlx, MLX_KEY_DOWN) || mlx_is_key_down(c->mlx, MLX_KEY_S))
		return (move(c, 0, 1));
	if (mlx_is_key_down(c->mlx, MLX_KEY_UP) || mlx_is_key_down(c->mlx, MLX_KEY_W))
		return (move(c, 0, -1));
}

void	move(t_cub *c, int move_x, int move_y) //
{
	if (!map_limits(c, move_x, move_y))
		return;

/* 	printf("c->p_y = %f c->p_x = %f\n", c->p_y + (move_y * STEP_SIZE / IMG_WIDHT), \
	c->p_x + (move_x * STEP_SIZE / IMG_WIDHT));
	printf("c->p_y_map = %i c->p_x_map = %i\n", c->p_x_floor, c->p_x_floor);
	
	c->map[c->p_y_floor][c->p_x_floor] = '0';
	if (mlx_image_to_window(c->mlx, c->img_floor, c->p_x * IMG_WIDHT, c->p_y * IMG_HEIGHT) < 1)
		return (c_error("Couldn't load image in move", c));
		
	printf("OLAOLA c->p_y = %f c->p_x = %f\n", c->p_y, c->p_x);
	

	
	printf("OLAOLA c->p_y = %f c->p_x = %f\n", c->p_y, c->p_x);
	
	c->map[c->p_y_floor][c->p_x_floor] = 'N';
	if (mlx_image_to_window(c->mlx, c->img_player, c->p_x * IMG_WIDHT, c->p_y * IMG_HEIGHT) < 1)
		return (c_error("Couldn't load image in player_move", c)); */
}

int	map_limits(t_cub *c, int move_x, int move_y)
{
	c->p_y_floor = (int)floor(c->p_y + (move_y * STEP_SIZE / IMG_WIDHT));
	c->p_x_floor = (int)floor(c->p_x + (move_x * STEP_SIZE / IMG_WIDHT));
	c->p_y_ceil = (int)ceil(c->p_y + (move_y * STEP_SIZE / IMG_WIDHT));
	c->p_x_ceil = (int)ceil(c->p_x + (move_x * STEP_SIZE / IMG_WIDHT));

	c->p_y = c->p_y + (move_y * STEP_SIZE / IMG_WIDHT);
	c->p_x = c->p_x + (move_x * STEP_SIZE / IMG_WIDHT);

	printf("move_x = %i move_y = %i\n", move_x, move_y);
	printf("c->p_y_floor = %i c->p_y = %f\n", c->p_y_floor, c->p_y);
	printf("c->p_x_floor = %i c->p_x = %f\n", c->p_x_floor, c->p_x);
	printf("c->p_y_ceil = %i c->p_y = %f\n", c->p_y_ceil, c->p_y);
	printf("c->p_x_ceil = %i c->p_x = %f\n", c->p_x_ceil, c->p_x);
	
	if (c->p_y_floor < 0 || c->p_y_ceil > c->map_axis_y || c->p_x_floor < 0 || c->p_y_ceil > c->map_axis_x)
		return (0);
		
	if (move_x == 1 && c->map[c->p_y_floor][c->p_x_ceil] != 0)
		return (0);
	if (move_x == -1 && c->map[c->p_y_floor][c->p_x_floor - 1] != 0)
		return (0);
	if (move_y == 1 && c->map[c->p_y_floor][c->p_x_floor] != 0)
		return (0);
	if (move_y == -1 && c->map[c->p_y_ceil - 1][c->p_x_floor] != 0)
		return (0);
		
	return (1);
}
