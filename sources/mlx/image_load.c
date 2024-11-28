/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:04:37 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/28 17:33:45 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	image_load(t_cub *c)
{
	//floor
	c->png_floor = ft_strdup("./textures/png/wolfestein/grey_wall.png");
	if (!c->png_floor)
		c_error("Couldn't alloc in initiate_cube", c);
	c->texture_floor = mlx_load_png(c->png_floor);
	if (!c->texture_floor)
		c_error_img(c->png_floor, c);
	c->img_floor = mlx_texture_to_image(c->mlx, c->texture_floor);
	if (!c->img_floor)
		c_error("Couldn't mlx_texture_to_image in image_load", c);
	mlx_image_to_window(c->mlx, c->img_floor, 0, 0); //por que es necesaria?

	//wall
	c->png_wall = ft_strdup("./textures/png/wolfestein/steel_wall.png");
	if (!c->png_wall)
		c_error("Couldn't alloc in initiate_cube", c);	
	c->texture_wall = mlx_load_png(c->png_wall);
	if (!c->texture_wall)
		c_error_img(c->png_wall, c);
	c->img_wall = mlx_texture_to_image(c->mlx, c->texture_wall);
	if (!c->img_wall)
		c_error("Couldn't mlx_texture_to_image in image_load", c);
	mlx_image_to_window(c->mlx, c->img_wall, 0, 0);	//por que es necesaria?

	//player
	c->png_player = ft_strdup("./textures/png/wolfestein/brick_wall.png");
	if (!c->png_player)
		c_error("Couldn't alloc in initiate_cube", c);	
	c->texture_player = mlx_load_png(c->png_player);
	if (!c->texture_player)
		c_error_img(c->png_player, c);
	c->img_player = mlx_texture_to_image(c->mlx, c->texture_player);
	if (!c->img_player)
		c_error("Couldn't mlx_texture_to_image in image_load", c);
	mlx_image_to_window(c->mlx, c->img_player, 0, 0);	//por que es necesaria?
	
// ...

}
