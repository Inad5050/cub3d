/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:35:49 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/07 21:44:06 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	init_game(t_cub *c)
{
	c->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "CUB3D", true); //inicializa la MLX
	if (!c->mlx)
		return (c_error("Couldn't mlx_init init_game", c), EXIT_FAILURE);
	c->win_mlx3D = mlx_new_image(c->mlx, WIN_WIDTH, WIN_HEIGHT); //inicializa la ventana
	if (!c->win_mlx3D)
		return (c_error("Couldn't mlx_new_image in init_game", c), EXIT_FAILURE);
	c->map = c->parse_struct->map;
	load_texture(c, &c->wall_n, c->parse_struct->north_texture); //carga las texturas en una estructura personalzada
	load_texture(c, &c->wall_s, c->parse_struct->south_texture);
	load_texture(c, &c->wall_w, c->parse_struct->west_texture);
	load_texture(c, &c->wall_e, c->parse_struct->east_texture);
	load_texture(c, &c->door_t, DOOR_ROUTE);

	load_texture(c, &c->sprite_t, SPRITE_ROUTE);

	c->floor = get_color_alt(c->parse_struct->floor_color); //consigue el color de suelo y techo en un solo int de 32 bytes
	c->ceiling = get_color_alt(c->parse_struct->ceiling_color);	
	c->map_max_y = c->parse_struct->max_y_size * TILE_SIZE;
	get_map_max_x(c); //obtenemos el tamaño maximo del eje x del mapa
	c->rays = ft_calloc(NUM_RAYS, sizeof(t_ray)); //inicializa las estrucuturas de los rayos
	if (!c->rays)
		return (c_error("Couldn't initiate init_game", c), EXIT_FAILURE);
	init_minimap(c);
	return (EXIT_SUCCESS);
}

int	load_texture(t_cub *c, t_texture **strc, char *route)
{
	mlx_texture_t	*png;
	
	*strc = ft_calloc(1, sizeof(t_texture)); //inicializa las estructuras de las texturas
	if (!*strc)
		return (c_error("Couldn't alloc in load_texture", c), EXIT_FAILURE);
	png = mlx_load_png(route); //load_png carga la informacion de la imagen en la estructura mlx_texture_t (nativa de la MLX).
	if (!png)
		return (c_error("Couldn't alloc in load_texture", c), EXIT_FAILURE);	
	load_texture_aux(c, *strc, png); //Pasamos los datos a t_texture que es una estructura propia	
	mlx_delete_texture(png); //liberamos mlx_texture_t
	return (EXIT_SUCCESS);
}

int	load_texture_aux(t_cub *c, t_texture *texture, mlx_texture_t *png)
{
	int				y;
	int				x;
	
	texture->height = png->height;
	texture->width = png->width;
	texture->pixels = ft_calloc(texture->height, sizeof(unsigned int *)); //inicializamos los punteros de la matriz que va a almacenar el valor de cada pixel, tantos punteros como lineas de pixeles
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
