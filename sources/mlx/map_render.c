/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:58:55 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/28 17:34:08 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	map_render(t_cub *c)
{
	int	y;
	int	x;

	y = 0;

	while (c->map[y])
	{
		x = 0;
		while (c->map[y][x])
		{
			map_identify(y, x, c);
			x++;
		}
	y++;		
	}	
}

void	map_identify(int y, int x, t_cub *c)
{
	
	if (c->map[y][x] == '0')
	{
		if (mlx_image_to_window(c->mlx, c->img_floor, x * IMG_WIDHT, y * IMG_HEIGHT) < 1)
			c_error("Couldn't image_print", c);
	}
	if (c->map[y][x] == '1')
	{
		if (mlx_image_to_window(c->mlx, c->img_wall, x * IMG_WIDHT, y * IMG_HEIGHT) < 1)
			c_error("Couldn't image_print", c);
	}
	if (c->map[y][x] == 'N')
	{
		c->player_y = y;
		c->player_x = x;
		if (mlx_image_to_window(c->mlx, c->img_player, x * IMG_WIDHT, y * IMG_HEIGHT) < 1)
			c_error("Couldn't image_print", c);
	}

	// ...
	
}
