/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:04:37 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/12 20:29:38 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//mlx_texture_t* mlx_load_png(const char* path);
//mlx_image_t* mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture);

void	image_load(t_cube *c)
{
	c->texture_floor = mlx_load_png(c->png_floor)
	if (!c->texture_floor)
		c_error_img(c->png_floor, c);
	c->img_floor = mlx_texture_to_image(c->mlx, c->texture_floor);
	
	c->texture_roof = mlx_load_png(c->png_roof)
	if (!c->texture_roof)
		c_error_img(c->png_roof, c);
	c->img_roof = mlx_texture_to_image(c->mlx, c->texture_floor);
	
// ...

}

//int32_t mlx_image_to_window(mlx_t* mlx, mlx_image_t* img, int32_t x, int32_t y);

void	image_draw(t_cube *c)
{
	mlx_image_to_window(c->mlx, c->img_floor, )
	
// ...

}