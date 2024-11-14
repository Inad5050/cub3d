/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:04:37 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/14 22:22:46 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	image_load(t_cube *c)
{

	ft_printf("image_load\n");
	
	c->texture_floor = mlx_load_png(c->png_floor);
	if (!c->texture_floor)
		c_error_img(c->png_floor, c);
	c->img_floor = mlx_texture_to_image(c->mlx, c->texture_floor);
	if (!c->img_floor)
		c_error("Couldn't mlx_texture_to_image in image_load", c);
		
	c->texture_wall = mlx_load_png(c->png_wall);
	if (!c->texture_wall)
		c_error_img(c->png_wall, c);
	c->img_wall = mlx_texture_to_image(c->mlx, c->texture_wall);
	if (!c->img_wall)
		c_error("Couldn't mlx_texture_to_image in image_load", c);
	
		
// ...

	map_render(c);
}

//int32_t mlx_image_to_window(mlx_t* mlx, mlx_image_t* img, int32_t x, int32_t y);

void	map_render(t_cube *c)
{
	
	ft_printf("map_render\n");
	
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
	
	ft_printf("map_identify y = %i, x = %i\n", x, y);
	
	if (c->map[y][x] == 0)
		image_print(c->img_floor, y, x, c);
	if (c->map[y][x] == 1)
		image_print(c->img_wall, y, x, c);

	// ...
	
}

void	image_print(mlx_image_t *img, int y, int x, t_cube *c)
{
	if (mlx_image_to_window(c->mlx, img, x * IMG_WIDHT, y * IMG_HEIGHT) < 1)
		c_error("Couldn't image_print", c);
}
