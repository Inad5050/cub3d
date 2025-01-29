/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:35:49 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/29 13:43:17 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	init_game(t_cub *c)
{
	c->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "SUPER CUB3D", true);
	if (!c->mlx)
		return (c_error("Couldn't initiate c->mlx", c), EXIT_FAILURE);
	c->win_mlx3D = mlx_new_image(c->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	init_t_texture(c, &c->wall_n);
	init_t_texture(c, &c->wall_s);
	init_t_texture(c, &c->wall_w);
	init_t_texture(c, &c->wall_e);
	c->ceiling = CEILING_COLOR;
	c->floor = FlOOR_COLOR;
	c->rays = ft_calloc(WIN_WIDHT, sizeof(t_ray));
	if (!c->rays)
			return (c_error("Couldn't initiate init_game", c), EXIT_FAILURE);
	init_texture(c, c->wall_n, ROUTE_NORTH);
	init_texture(c, c->wall_s, ROUTE_SHOUT);
	init_texture(c, c->wall_w, ROUTE_WEST);
	init_texture(c, c->wall_e, ROUTE_EAST);
	locate_player(c);
	c->player_fov = (60 * PI / 180); //para un Field of View (FOV) de 60 grados. Siempre sera el mismo (aprox 1.66)
	return (EXIT_SUCCESS);
}

int	init_t_texture(t_cub *c, t_texture **strc)
{
	*strc = ft_calloc(1, sizeof(t_texture));
	if (!*strc)
			return (c_error("Couldn't alloc in init_t_texture", c), EXIT_FAILURE);
	return (0);
}

int	init_texture(t_cub *c, t_texture *texture, char *route) //load_png carga la informacion de la imagen en la estructura mlx_texture_t (nativa de la MLX). Nosotros pasamos los datos a t_texture que es una estructura propia
{
	mlx_texture_t	*png;
	int				y;
	int				x;
	
	png = mlx_load_png(route); //cargamos el buffer con la ingormacion del png
	if (!png)
		return (c_error("Couldn't load_png in init_image", c), EXIT_FAILURE);
	texture->height = png->height; //rellenamos nuestra estructura
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
		{
			texture->pixels[y][x] = get_color(&png->pixels[(y * png->width + x) * png->bytes_per_pixel]); //png->pixels es un solo string de uint8_t. Podemos localizar el puntero al valor de cada pixel multiplicando el numero de filas que ya hemos recorrido (y) * el tamaño de la fila (widht) + los uint8_t que ya hemos recorrido de la siguiente fila. bytes_per_pixel sera siempre 8 (?) y nos da una idea de cuanto espacio ocupa el color de cada pixel
			/* printf("texture->pixels[%d][%d] = %u\n", y, x, texture->pixels[y][x]); */
		}
		y++;
	}
	mlx_delete_texture(png); //liberamos el buffer del png	
	return (0);
}

uint32_t	get_color(uint8_t *ptr) //load_png almacena el valor del color de los pixeles en estructuras de 4 integers de 8 bytes. Queremos combinar esos numeros en uno solo de 32 bytes.
{
	uint32_t	b; //blue
	uint32_t	g; //green
	uint32_t	r; //red
	uint32_t	a; //alpha. opacidad (?)

	r = (uint32_t)*(ptr);
	g = (uint32_t)*(ptr + 1);
	b = (uint32_t)*(ptr + 2);
	a = (uint32_t)*(ptr + 3);
	return ((r << 24) + (g << 16) + (b << 8) + a);
}