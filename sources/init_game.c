/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:35:49 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/30 19:00:43 by dangonz3         ###   ########.fr       */
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
	init_texture_struct(c, &c->wall_n, ROUTE_NORTH);
	init_texture_struct(c, &c->wall_s, ROUTE_SHOUT);
	init_texture_struct(c, &c->wall_w, ROUTE_WEST);
	init_texture_struct(c, &c->wall_e, ROUTE_EAST);
	c->ceiling = CEILING_COLOR;
	c->floor = FlOOR_COLOR;
	c->rays = ft_calloc(WIN_WIDHT, sizeof(t_ray));
	if (!c->rays)
		return (c_error("Couldn't initiate init_game", c), EXIT_FAILURE);
	
/* 	printf("c->wall_n->height = %d, c->wall_n->width = %d, c->wall_n->pixels[0][0] = %u\n", c->wall_n->height, c->wall_n->width, c->wall_n->pixels[0][0]);
	printf("c->wall_s->height = %d, c->wall_s->width = %d, c->wall_s->pixelsP[0][0] = %u\n", c->wall_s->height, c->wall_s->width, c->wall_s->pixels[0][0]);
	printf("c->wall_w->height = %d, c->wall_w->width = %d, c->wall_w->pixelsP[0][0] = %u\n", c->wall_w->height, c->wall_w->width, c->wall_w->pixels[0][0]);
	printf("c->wall_e->height = %d, c->wall_e->width = %d, c->wall_e->pixelsP[0][0] = %u\n", c->wall_e->height, c->wall_e->width, c->wall_e->pixels[0][0]);
 */	
	return (EXIT_SUCCESS);
}

int	init_texture_struct(t_cub *c, t_texture **strc, char *route)
{
	mlx_texture_t	*png;
	
	*strc = ft_calloc(1, sizeof(t_texture)); //alojamos memoria en la localizacion del puntero
	if (!*strc)
		return (c_error("Couldn't alloc in init_texture_struct", c), EXIT_FAILURE);
	png = mlx_load_png(route); //cargamos mlx_texture_t con la informacion del png
	if (!png)
		return (c_error("Couldn't alloc in init_texture_struct", c), EXIT_FAILURE);

	/* printf("(*strc)->height = %d, (*strc)->width = %d\n", (*strc)->height, (*strc)->width); */
	
	init_texture_struct_aux(c, *strc, png);

	/* 	printf("(*strc)->height = %d, (*strc)->width = %d, (*strc)->pixels[0][0] = %u\n", (*strc)->height, (*strc)->width, (*strc)->pixels[0][0]);
		printf("png->height = %d, png->width = %d, png->pixels[0] = %u\n", png->height, png->width, png->pixels[0]); */
	
	mlx_delete_texture(png);
	return (EXIT_SUCCESS);
}

int	init_texture_struct_aux(t_cub *c, t_texture *texture, mlx_texture_t	*png) //load_png carga la informacion de la imagen en la estructura mlx_texture_t (nativa de la MLX). Pasamos los datos a t_texture que es una estructura propia
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
