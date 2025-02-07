/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:55:44 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/07 21:25:29 by dangonz3         ###   ########.fr       */
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
			mlx_put_pixel(c->win_mlx3D, x++ + x_map * c->minimap_tile_size + c->minimap_start_x, 
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
/* 			if (minimap_next_wall(x + c->p_x / TILE_SIZE * c->minimap_tile_size + c->minimap_start_x,
			y + c->p_y / TILE_SIZE * c->minimap_tile_size + c->minimap_start_y, c))
				return; */
			mlx_put_pixel(c->win_mlx3D, 
			x + c->p_x / TILE_SIZE * c->minimap_tile_size + c->minimap_start_x, 
			y + c->p_y / TILE_SIZE * c->minimap_tile_size + c->minimap_start_y, RED);
			x++;
		}
		y++;
	}	
}

/* int	minimap_next_wall(float x, float y, t_cub *c)
{
	float		player_edge_x;
	float		player_edge_y;
	float		current_tile_start_x;
	float		current_tile_start_y;
	float		current_tile_edge_x;
	float		current_tile_edge_y;
	char	next_tile_content_x;
	char	next_tile_content_y;

	player_edge_x = x + c->minimap_player_size;
	player_edge_y = y + c->minimap_player_size;
	current_tile_start_x = c->minimap_start_x + (int)(c->p_x / TILE_SIZE) * c->minimap_tile_size;
	current_tile_start_y = c->minimap_start_y + (int)(c->p_y / TILE_SIZE) * c->minimap_tile_size;
	printf("current_tile_start_x %f = c->minimap_start_x %f + (int)(c->p_x / TILE_SIZE) %d * c->minimap_tile_size %f\n", current_tile_start_x, c->minimap_start_x, (int)(c->p_x / TILE_SIZE), c->minimap_tile_size);
	current_tile_edge_x = current_tile_start_x + c->minimap_tile_size;
	current_tile_edge_y = current_tile_start_y + c->minimap_tile_size;
	next_tile_content_x = c->map[(int)(current_tile_start_x / TILE_SIZE) + 1][(int)(current_tile_start_y / TILE_SIZE)];
	next_tile_content_y = c->map[(int)current_tile_start_x / TILE_SIZE][(int)(current_tile_edge_y / TILE_SIZE) + 1];
	printf("player_edge_x %f > current_tile_edge_x %f && next_tile_content_x %c\n", player_edge_x, current_tile_edge_x, next_tile_content_x);
	if (player_edge_x > current_tile_edge_x && next_tile_content_x == '1')
		return (printf("OLAOLA1\n"), 1);
	if (player_edge_y > current_tile_edge_y && next_tile_content_y == '1')
		return (printf("OLAOLA2\n"), 1);
	return (0);
} */

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
