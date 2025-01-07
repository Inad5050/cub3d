/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:35:49 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/07 17:00:14 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	init_game(t_cub *c)
{
	c->mlx = mlx_init(c); //inicializa MLX
	if (!c->mlx)
		return (c_error("Couldn't initiate c->mlx", c), EXIT_FAILURE);
	c->win_mlx = mlx_new_window(c->mlx, c->map_axis_x * IMG_WIDHT, \
	c->map_axis_y * IMG_HEIGHT, "Cube3d"); //crea la ventana
	if (!c->win_mlx)
		return (c_error("Couldn't initiate c->win", c), EXIT_FAILURE);
	c->p = ft_calloc(1, sizeof(t_player)); //inicializa la estructura t_player
	if (!c->p)
		return (c_error("Couldn't alloc c->p", c), EXIT_FAILURE);
	init_image(c, &c->ceiling, ROUTE_CEILING); //inicializa la estructura de cada imagen
	init_image(c, &c->floor, ROUTE_FlOOR);
	init_image(c, &c->wall_n, ROUTE_NORTH);
	init_image(c, &c->wall_s, ROUTE_SHOUT);
	init_image(c, &c->wall_w, ROUTE_WEST);
	init_image(c, &c->wall_e, ROUTE_EAST);
	init_player_image(c, &c->player_img, ROUTE_PLAYER);
	return (EXIT_SUCCESS);
}

int	init_image(t_cub *c, t_img **c_img_ptr, char *route) //inicializa la estructura de cada imagen
{
	t_img	*c_img;
	
	*c_img_ptr = ft_calloc(1, sizeof(t_img)); //aloja memoria para la estructura t_img
	if (!*c_img_ptr)
		return (c_error("Couldn't alloc *c_img_ptr", c), EXIT_FAILURE);
	c_img = *c_img_ptr;
	c_img->height = IMG_HEIGHT; //guardamos el valor en ints para referenciarlos en mlx_get_data_addr
	c_img->width = IMG_WIDHT;
	c_img->img_ptr = mlx_xpm_file_to_image(c->mlx, route, &(c_img->width), &(c_img->height)); //accedemos a la imagen desde la ruta correspondiente y obtenemos un puntero a la misma
	if (!c_img->img_ptr)
		return (c_error("Couldn't mlx_xpm_file_to_image", c), EXIT_FAILURE);
	c_img->addr = mlx_get_data_addr(c_img->img_ptr, &(c_img->bpp), \
		&(c_img->line_len), &(c_img->endian)); //obtenemos el bpp , la line_len y el endian de la imagen
	return (EXIT_SUCCESS);
}

int	init_player_image(t_cub *c, t_img **c_img_ptr, char *route) //inicializa la estructura de la imagen del jugador
{
	t_img	*c_img;
	
	*c_img_ptr = ft_calloc(1, sizeof(t_img)); //aloja memoria para la estructura t_img
	if (!*c_img_ptr)
		return (c_error("Couldn't alloc *c_img_ptr", c), EXIT_FAILURE);
	c_img = *c_img_ptr;
	c_img->height = 32; //guardamos el valor en ints para referenciarlos en mlx_get_data_addr
	c_img->width = 32;
	c_img->img_ptr = mlx_xpm_file_to_image(c->mlx, route, &(c_img->width), &(c_img->height)); //accedemos a la imagen desde la ruta correspondiente y obtenemos un puntero a la misma
	if (!c_img->img_ptr)
		return (c_error("Couldn't mlx_xpm_file_to_image", c), EXIT_FAILURE);
	c_img->addr = mlx_get_data_addr(c_img->img_ptr, &(c_img->bpp), \
		&(c_img->line_len), &(c_img->endian)); //obtenemos el bpp , la line_len y el endian de la imagen
	return (EXIT_SUCCESS);
}
