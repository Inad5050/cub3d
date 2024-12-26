/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:58:55 by dangonz3          #+#    #+#             */
/*   Updated: 2024/12/26 23:37:33 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	map_render(t_cub *c) //recorre la matriz del mapa
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

void	map_identify(int y, int x, t_cub *c) //identifica cada elemento del mapa y lo imprime en la pantalla
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
		if (!c->p_y && !c->p_x)
		{
			c->p_y = (double)y;
			c->p_x = (double)x;
		}
		
		printf("OLAOLA c->p_y = %f c->p_x = %f\n", c->p_y, c->p_x);
		
		if (mlx_image_to_window(c->mlx, c->img_player, x * IMG_WIDHT, y * IMG_HEIGHT) < 1)
			c_error("Couldn't image_print", c);
	}

	// ...
	
}
