/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:17:26 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/28 19:45:10 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	player_move(t_cub *c)
{
	if (mlx_is_key_down(c->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(c->mlx, MLX_KEY_D))
		move(c, 1);
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT) || mlx_is_key_down(c->mlx, MLX_KEY_A))
		move(c, 2);
	if (mlx_is_key_down(c->mlx, MLX_KEY_DOWN) || mlx_is_key_down(c->mlx, MLX_KEY_S))
		move(c, 3);
	if (mlx_is_key_down(c->mlx, MLX_KEY_UP) || mlx_is_key_down(c->mlx, MLX_KEY_W))
		move(c, 4);
	
	c->map[c->p_y][c->p_x] = 'N';
	if (mlx_image_to_window(c->mlx, c->img_player, c->p_x * IMG_WIDHT, c->p_y * IMG_HEIGHT) < 1)
			return (c_error("Couldn't load image in player_move", c));
}

void 	move(t_cub *c, int n)
{
	ft_printf("OLA c->p_y = %i ; c->p_x = %i\n", c->p_y, c->p_x);
	
	if (n == 1 && \
	c->p_y > 0 && c->p_y < c->map_axis_y && c->p_x > 0 && c->p_x < c->map_axis_x)
	{
		if (c->map[c->p_y][c->p_x + 1] != '0')
			return;

		c->map[c->p_y][c->p_x] = '0';
		if (mlx_image_to_window(c->mlx, c->img_floor, c->p_x * IMG_WIDHT, c->p_y * IMG_HEIGHT) < 1)
			return (c_error("Couldn't load image in move", c));	
			
		c->p_x = c->p_x + 1;

		c->map[c->p_y][c->p_x] = 'N';
		if (mlx_image_to_window(c->mlx, c->img_player, c->p_x * IMG_WIDHT, c->p_y * IMG_HEIGHT) < 1)
			return (c_error("Couldn't load image in player_move", c));
	}
	if (n == 2 && \
	c->p_y > 0 && c->p_y < c->map_axis_y && c->p_x > 0 && c->p_x < c->map_axis_x)
	{
		if (c->map[c->p_y][c->p_x + 1]  != '0')
			return;
		
		c->map[c->p_y][c->p_x] = '0';
		if (mlx_image_to_window(c->mlx, c->img_floor, c->p_x * IMG_WIDHT, c->p_y * IMG_HEIGHT) < 1)
			return (c_error("Couldn't load image in move", c));	
			
		c->p_x = c->p_x - 1;

		c->map[c->p_y][c->p_x] = 'N';
		if (mlx_image_to_window(c->mlx, c->img_player, c->p_x * IMG_WIDHT, c->p_y * IMG_HEIGHT) < 1)
			return (c_error("Couldn't load image in player_move", c));
	}
	if (n == 3 && \
	c->p_y > 0 && c->p_y < c->map_axis_y && c->p_x > 0 && c->p_x < c->map_axis_x)
	{
		if (c->map[c->p_y + 1][c->p_x]  != '0')
			return;
		
		c->map[c->p_y][c->p_x] = '0';
		if (mlx_image_to_window(c->mlx, c->img_floor, c->p_x * IMG_WIDHT, c->p_y * IMG_HEIGHT) < 1)
			return (c_error("Couldn't load image in move", c));
		
		c->p_y = c->p_y + 1;

		c->map[c->p_y][c->p_x] = 'N';
		if (mlx_image_to_window(c->mlx, c->img_player, c->p_x * IMG_WIDHT, c->p_y * IMG_HEIGHT) < 1)
			return (c_error("Couldn't load image in player_move", c));
	}
	if (n == 4 && \
	c->p_y > 0 && c->p_y < c->map_axis_y && c->p_x > 0 && c->p_x < c->map_axis_x)
	{
		if (c->map[c->p_y - 1][c->p_x]  != '0')
			return;
		
		c->map[c->p_y][c->p_x] = '0';
		if (mlx_image_to_window(c->mlx, c->img_floor, c->p_x * IMG_WIDHT, c->p_y * IMG_HEIGHT) < 1)
			return (c_error("Couldn't load image in move", c));
		
		c->p_y = c->p_y - 1;

		c->map[c->p_y][c->p_x] = 'N';
		if (mlx_image_to_window(c->mlx, c->img_player, c->p_x * IMG_WIDHT, c->p_y * IMG_HEIGHT) < 1)
			return (c_error("Couldn't load image in player_move", c));
	}

	ft_printf("c->p_y = %i ; c->p_x = %i\n", c->p_y, c->p_x);
}
