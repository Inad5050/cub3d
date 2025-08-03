/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:35:49 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/21 17:56:05 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	init_game(t_cub *c, t_parse *p)
{
	c->parse_struct = p;
	c->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "CUB3D", true);
	if (!c->mlx)
		return (c_error("Couldn't mlx_init init_game", c), EXIT_FAILURE);
	c->win_mlx3d = mlx_new_image(c->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!c->win_mlx3d)
		return (c_error("Couldn't mlx_new_image in init_game", c), \
			EXIT_FAILURE);
	c->map = p->map;
	load_texture(c, c->wall_n, p->north_texture);
	load_texture(c, c->wall_s, p->south_texture);
	load_texture(c, c->wall_w, p->west_texture);
	load_texture(c, c->wall_e, p->east_texture);
	load_texture(c, c->door_t, DOOR_ROUTE);
	c->floor = get_color_alt(p->floor_color);
	c->ceiling = get_color_alt(p->ceiling_color);
	c->map_max_y = p->max_y_size * TILE_SIZE;
	c->map_max_x = get_map_max_x(c);
	c->rays = ft_calloc(NUM_RAYS, sizeof(t_ray));
	if (!c->rays)
		return (c_error("Couldn't initiate init_game", c), EXIT_FAILURE);
	init_minimap(c);
	return (EXIT_SUCCESS);
}

int	load_texture(t_cub *c, t_texture *texture, char *route)
{
	mlx_texture_t	*png;

	texture = ft_calloc(1, sizeof(t_texture));
	if (!texture)
		return (c_error("Couldn't alloc in load_texture", c), EXIT_FAILURE);
	png = mlx_load_png(route);
	if (!png)
		return (c_error("Couldn't alloc in load_texture", c), EXIT_FAILURE);
	load_texture_aux(c, texture, png);
	mlx_delete_texture(png);
	return (EXIT_SUCCESS);
}

int	load_texture_aux(t_cub *c, t_texture *texture, mlx_texture_t *png)
{
	int				y;
	int				x;

	texture->height = png->height;
	texture->width = png->width;
	texture->pixels = ft_calloc(texture->height, sizeof(unsigned int *));
	if (!texture->pixels)
		return (mlx_delete_texture(png), \
			c_error("Couldn't aloc in init_image", c), EXIT_FAILURE);
	y = 0;
	while (y < texture->height)
	{
		texture->pixels[y] = ft_calloc(texture->width, sizeof(unsigned int));
		if (!texture->pixels[y])
			return (mlx_delete_texture(png), \
				c_error("Couldn't aloc in init_image", c), EXIT_FAILURE);
		x = -1;
		while (++x < texture->width)
			texture->pixels[y][x] = get_color(&png->pixels[(y * \
				png->width + x) * png->bytes_per_pixel]);
		y++;
	}
	return (EXIT_SUCCESS);
}

int	get_map_max_x(t_cub *c)
{
	int	i;
	int	new_max;
	int	current_max;

	i = 0;
	current_max = 0;
	while (i <= c->map_max_y / TILE_SIZE)
	{
		new_max = (int)ft_strlen((const char *)c->map[i]) * TILE_SIZE;
		if (new_max > current_max)
			current_max = new_max;
		i++;
	}
	return (current_max);
}
