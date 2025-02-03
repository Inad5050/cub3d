/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:35:49 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/03 16:54:51 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	init_game(t_cub *c)
{
	c->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "SUPER CUB3D", true);
	if (!c->mlx)
		return (c_error("Couldn't mlx_init init_game", c), EXIT_FAILURE);
	c->win_mlx3D = mlx_new_image(c->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!c->win_mlx3D)
		return (c_error("Couldn't mlx_new_image in init_game", c), EXIT_FAILURE);
	c->map = c->parse_struct->map;
	load_texture(c, &c->wall_n, c->parse_struct->north_texture);
	load_texture(c, &c->wall_s, c->parse_struct->south_texture);
	load_texture(c, &c->wall_w, c->parse_struct->west_texture);
	load_texture(c, &c->wall_e, c->parse_struct->east_texture);
	c->floor = get_color_alt(c->parse_struct->floor_color);
	c->ceiling = get_color_alt(c->parse_struct->ceiling_color);	
	c->map_max_y = c->parse_struct->max_y_size * TILE_SIZE;
	get_map_max_x(c);	
	c->rays = ft_calloc(WIN_WIDHT, sizeof(t_ray));
	if (!c->rays)
		return (c_error("Couldn't initiate init_game", c), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	load_texture(t_cub *c, t_texture **strc, char *route)
{
	mlx_texture_t	*png;
	
	*strc = ft_calloc(1, sizeof(t_texture)); //alojamos memoria en la localizacion del puntero
	if (!*strc)
		return (c_error("Couldn't alloc in load_texture", c), EXIT_FAILURE);
	png = mlx_load_png(route); //cargamos mlx_texture_t con la informacion del png
	if (!png)
		return (c_error("Couldn't alloc in load_texture", c), EXIT_FAILURE);	
	load_texture_aux(c, *strc, png);	
	mlx_delete_texture(png);
	return (EXIT_SUCCESS);
}

int	load_texture_aux(t_cub *c, t_texture *texture, mlx_texture_t	*png) //load_png carga la informacion de la imagen en la estructura mlx_texture_t (nativa de la MLX). Pasamos los datos a t_texture que es una estructura propia
{
	int				y;
	int				x;
	
	texture->height = png->height;
	texture->width = png->width;
	texture->pixels = ft_calloc(texture->height, sizeof(unsigned int *));
	if (!texture->pixels)
		return (mlx_delete_texture(png), c_error("Couldn't aloc in init_image", c), EXIT_FAILURE);
	y = 0;
	while (y < texture->height) //rellenamos texture->pixels
	{
		texture->pixels[y] = ft_calloc(texture->width, sizeof(unsigned int));
		if (!texture->pixels[y])
			return (mlx_delete_texture(png), c_error("Couldn't aloc in init_image", c), EXIT_FAILURE);
		x = -1;
		while (++x < texture->width)
			texture->pixels[y][x] = get_color(&png->pixels[(y * png->width + x) * png->bytes_per_pixel]); //png->pixels es un solo string de uint8_t. Podemos localizar el puntero al valor de cada pixel multiplicando el numero de filas que ya hemos recorrido (y) * el tamaño de la fila (widht) + los uint8_t que ya hemos recorrido de la siguiente fila. bytes_per_pixel sera siempre 8 (?) y nos da una idea de cuanto espacio ocupa el color de cada pixel
		y++;
	}
	return (EXIT_SUCCESS);
}

void	get_map_max_x(t_cub *c)
{
	int	i;
	int	new_max;

	i = 0;
	while (i <= c->map_max_y / TILE_SIZE)
	{
		new_max = (int)ft_strlen((const char *)c->map[i]) * TILE_SIZE;
		if (new_max > (c->map_max_x))
			(c->map_max_x) = new_max;
		i++;
	}	
}