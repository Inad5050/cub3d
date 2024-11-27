/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:04:37 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/27 18:56:44 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	image_load(t_cube *c)
{
	c->png_floor = ft_strdup("./textures/png/wolfestein/grey_wall.png");
	if (!c->png_floor)
		c_error("Couldn't alloc in initiate_cube", c);
	c->texture_floor = mlx_load_png(c->png_floor);
	if (!c->texture_floor)
		c_error_img(c->png_floor, c);
	c->img_floor = mlx_texture_to_image(c->mlx, c->texture_floor);
	if (!c->img_floor)
		c_error("Couldn't mlx_texture_to_image in image_load", c);

	c->png_wall = ft_strdup("./textures/png/wolfestein/steel_wall.png");
	if (!c->png_wall)
		c_error("Couldn't alloc in initiate_cube", c);	
	c->texture_wall = mlx_load_png(c->png_wall);
	if (!c->texture_wall)
		c_error_img(c->png_wall, c);
	c->img_wall = mlx_texture_to_image(c->mlx, c->texture_wall);
	if (!c->img_wall)
		c_error("Couldn't mlx_texture_to_image in image_load", c);
	
	mlx_image_to_window(c->mlx, c->img_floor, 0, 0); //por que son necesarias?
	mlx_image_to_window(c->mlx, c->img_wall, 0, 0);	//por que son necesarias?
	
// ...

	map_render(c);
}

void	map_render(t_cube *c)
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

void	map_identify(int y, int x, t_cube *c)
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

	// ...
	
}
