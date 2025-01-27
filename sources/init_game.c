/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:35:49 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/27 15:25:05 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	init_game(t_cub *c)
{
	c->mlx = mlx_init(c); //inicializa MLX
	if (!c->mlx)
		return (c_error("Couldn't initiate c->mlx", c), EXIT_FAILURE);
	c->win_mlx_2D = mlx_new_window(c->mlx, c->map_axis_x * CELL_WIDHT, \
	c->map_axis_y * CELL_HEIGHT, "Cube3d"); //crea la ventana 2D
	if (!c->win_mlx_2D)
		return (c_error("Couldn't initiate c->win2D", c), EXIT_FAILURE);
	c->win_mlx_3D = mlx_new_window(c->mlx, WIN_WIDHT, WIN_HEIGHT, "Cube3d");
	if (!c->win_mlx_3D)
		return (c_error("Couldn't initiate c->win3D", c), EXIT_FAILURE);
	init_image(c, &c->ceiling, ROUTE_CEILING); //inicializa la estructura de cada imagen
	init_image(c, &c->floor, ROUTE_FlOOR);
	init_image(c, &c->wall_n, ROUTE_NORTH);
	init_image(c, &c->wall_s, ROUTE_SHOUT);
	init_image(c, &c->wall_w, ROUTE_WEST);
	init_image(c, &c->wall_e, ROUTE_EAST);
	init_player_image(c, &c->player_img, ROUTE_PLAYER);
	locate_player(c);
	c->player_fov = (60 * PI / 180); //para un Field of View (FOV) de 60 grados. Siempre sera el mismo (aprox 1.66)
	return (EXIT_SUCCESS);
}

int	init_image(t_cub *c, t_img **c_img_ptr, char *route) //inicializa la estructura de cada imagen
{
	t_img	*c_img;
	
	*c_img_ptr = ft_calloc(1, sizeof(t_img)); //aloja memoria para la estructura t_img
	if (!*c_img_ptr)
		return (c_error("Couldn't alloc *c_img_ptr", c), EXIT_FAILURE);
	c_img = *c_img_ptr;
	c_img->img_height = CELL_HEIGHT; //guardamos el valor en ints para referenciarlos en mlx_get_data_addr
	c_img->img_width = CELL_WIDHT;
	
	c_img->img_ptr = mlx_xpm_file_to_image(c->mlx, route, &(c_img->img_width), &(c_img->img_height)); //accedemos a la imagen desde la ruta correspondiente y obtenemos un puntero a la misma
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
	c_img->img_width = PLAYER_WIDHT; //guardamos el valor en ints para referenciarlos en mlx_get_data_addr
	c_img->img_height = PLAYER_HEIGHT;
	c_img->img_ptr = mlx_xpm_file_to_image(c->mlx, route, &(c_img->img_width), &(c_img->img_height)); //accedemos a la imagen desde la ruta correspondiente y obtenemos un puntero a la misma
	if (!c_img->img_ptr)
		return (c_error("Couldn't mlx_xpm_file_to_image", c), EXIT_FAILURE);
	c_img->addr = mlx_get_data_addr(c_img->img_ptr, &(c_img->bpp), \
		&(c_img->line_len), &(c_img->endian)); //obtenemos el bpp, la line_len y el endian de la imagen
	return (EXIT_SUCCESS);
}
