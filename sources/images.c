/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:04:37 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/27 17:27:41 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	image_load(t_cube *c)
{
	c->png_floor = ft_strdup("./textures/png/wolfestein/grey_wall.png");
	if (!c->png_floor)
		c_error("Couldn't alloc in initiate_cube", c);
	
	ft_printf("SALUDOS\n");
	ft_printf("c->png_floor = %s\n", c->png_floor);

/* typedef struct mlx_texture
{
	uint32_t	width;
	uint32_t	height;
	uint8_t		bytes_per_pixel;
	uint8_t*	pixels;
}	mlx_texture_t; */
	
	c->texture_floor = mlx_load_png(c->png_floor);
	if (!c->texture_floor)
		c_error_img(c->png_floor, c);

/* 	printf("c->texture_floor.width = %u\n", c->texture_floor->width);
	printf("c->texture_floor.height = %u\n", c->texture_floor->height);
	printf("c->texture_floor.bytes_per_pixel = %hhu\n", c->texture_floor->bytes_per_pixel);
	printf("c->texture_floor.pixels = %s\n", c->texture_floor->pixels); */
		
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
		
// ...

	mlx_image_to_window(c->mlx, c->img_floor, 0, 0);
	ft_printf("image_load c->img_floor = %p\n", c->img_floor);

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
	
	/* ft_printf("map_identify c->img_floor = %p\n", c->img_floor); */
	
	
	if (c->map[y][x] == '0')
	{
		if (mlx_image_to_window(c->mlx, c->img_floor, x * IMG_WIDHT, y * IMG_HEIGHT) < 1)
			c_error("Couldn't image_print", c);
	}
	if (c->map[y][x] == '1')
	{
		if (mlx_image_to_window(c->mlx, c->img_floor, x * IMG_WIDHT, y * IMG_HEIGHT) < 1)
			c_error("Couldn't image_print", c);
	}

	// ...
	
}

void	image_print(mlx_image_t *img, int y, int x, t_cube *c)
{
	ft_printf("image_print c->img_floor = %p\n", img);
	
	if (!img)
		c_error("Invalid img in image_print", c);	
	if (mlx_image_to_window(c->mlx, img, x * IMG_WIDHT, y * IMG_HEIGHT) < 1)
		c_error("Couldn't image_print", c);
}

/* void	map_identify(int y, int x, t_cube *c)
{
	
	if (c->map[y][x] == '0')
	{
		ft_printf("c->map[y][x] = %c\n", c->map[y][x]);
		image_print(c->img_floor, y, x, c);
	}
	if (c->map[y][x] == '1')
	{
		ft_printf("c->map[y][x] = %c\n", c->map[y][x]);
		image_print(c->img_wall, y, x, c);
	}

	// ...
	
}

void	image_print(mlx_image_t *img, int y, int x, t_cube *c)
{
	ft_printf("image_print c->img_floor = %p\n", img);
	
	if (!img)
		c_error("Invalid img in image_print", c);	
	if (mlx_image_to_window(c->mlx, img, x * IMG_WIDHT, y * IMG_HEIGHT) < 1)
		c_error("Couldn't image_print", c);
} */