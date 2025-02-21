/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:55:44 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/21 16:35:06 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	minimap_render(t_cub *c)
{
	int		y;
	int		x;

	y = 0;
	while (y <= c->map_max_y / TILE_SIZE)
	{
		x = 0;
		while (x <= c->map_max_x / TILE_SIZE)
		{
			if (c->map[y][x] == '0')
				minimap_print(x, y, BLUE, c);
			if (c->map[y][x] == '1')
				minimap_print(x, y, BLACK, c);
			x++;
		}
		y++;
	}
	minimap_print_player(c);
}

void	minimap_print(int x_map, int y_map, uint32_t element, t_cub *c)
{
	int	x;
	int	y;

	y = 0;
	while (y < c->minimap_tile_size)
	{
		x = 0;
		while (x < c->minimap_tile_size)
			mlx_put_pixel(c->win_mlx3d, x++ + x_map * \
				c->minimap_tile_size + c->minimap_start_x,
				y + y_map * c->minimap_tile_size + c->minimap_start_y, element);
		y++;
	}
}

void	minimap_print_player(t_cub *c)
{
	int	x;
	int	y;

	y = 0;
	while (y < c->minimap_player_size)
	{
		x = 0;
		while (x < c->minimap_player_size)
		{
			mlx_put_pixel(c->win_mlx3d,
				x + c->p_x / TILE_SIZE * c->minimap_tile_size + \
				c->minimap_start_x,
				y + c->p_y / TILE_SIZE * c->minimap_tile_size + \
				c->minimap_start_y, RED);
			x++;
		}
		y++;
	}
}

void	init_minimap(t_cub *c)
{
	c->minimap_start_x = WIN_WIDTH * 0.02;
	c->minimap_start_y = WIN_HEIGHT * 0.02;
	c->minimap_area_x = 0.3 * WIN_WIDTH;
	c->minimap_area_y = 0.3 * WIN_HEIGHT;
	c->minimap_tile_size = c->minimap_area_x / (c->map_max_x / TILE_SIZE);
	if (c->minimap_area_y / (c->map_max_y / TILE_SIZE) < c->minimap_tile_size)
		c->minimap_tile_size = c->minimap_area_y / (c->map_max_y / TILE_SIZE);
	c->minimap_player_size = c->minimap_tile_size / 3;
}
