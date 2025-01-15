/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:35:49 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/15 13:11:18 by dangonz3         ###   ########.fr       */
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
	init_ply_image(c, &c->player_img, ROUTE_PLAYER);
	locate_player(c);
	init_3D(c);
	return (EXIT_SUCCESS);
}

int	init_image(t_cub *c, t_img **c_img_ptr, char *route) //inicializa la estructura de cada imagen
{
	t_img	*c_img;
	
	*c_img_ptr = ft_calloc(1, sizeof(t_img)); //aloja memoria para la estructura t_img
	if (!*c_img_ptr)
		return (c_error("Couldn't alloc *c_img_ptr", c), EXIT_FAILURE);
	c_img = *c_img_ptr;
	c_img->height = CELL_HEIGHT; //guardamos el valor en ints para referenciarlos en mlx_get_data_addr
	c_img->width = CELL_WIDHT;
	c_img->img_ptr = mlx_xpm_file_to_image(c->mlx, route, &(c_img->width), &(c_img->height)); //accedemos a la imagen desde la ruta correspondiente y obtenemos un puntero a la misma
	if (!c_img->img_ptr)
		return (c_error("Couldn't mlx_xpm_file_to_image", c), EXIT_FAILURE);
	c_img->addr = mlx_get_data_addr(c_img->img_ptr, &(c_img->bpp), \
		&(c_img->line_len), &(c_img->endian)); //obtenemos el bpp , la line_len y el endian de la imagen
	return (EXIT_SUCCESS);
}

int	init_ply_image(t_cub *c, t_img **c_img_ptr, char *route) //inicializa la estructura de la imagen del jugador
{
	t_img	*c_img;
	
	*c_img_ptr = ft_calloc(1, sizeof(t_img)); //aloja memoria para la estructura t_img
	if (!*c_img_ptr)
		return (c_error("Couldn't alloc *c_img_ptr", c), EXIT_FAILURE);
	c_img = *c_img_ptr;
	c_img->height = PLAYER_WIDHT; //guardamos el valor en ints para referenciarlos en mlx_get_data_addr
	c_img->width = PLAYER_HEIGHT;
	c_img->img_ptr = mlx_xpm_file_to_image(c->mlx, route, &(c_img->width), &(c_img->height)); //accedemos a la imagen desde la ruta correspondiente y obtenemos un puntero a la misma
	if (!c_img->img_ptr)
		return (c_error("Couldn't mlx_xpm_file_to_image", c), EXIT_FAILURE);
	c_img->addr = mlx_get_data_addr(c_img->img_ptr, &(c_img->bpp), \
		&(c_img->line_len), &(c_img->endian)); //obtenemos el bpp, la line_len y el endian de la imagen
	return (EXIT_SUCCESS);
}

void	*locate_player(t_cub *c) //localiza la posición inicial del jugador y coloca suelo '0' en su lugar
{
	int	y;
	int	x;

	y = 0;
	while (c->map[y])
	{
		x = 0;
		while (c->map[y][x])
		{
			if (c->map[y][x] == 'N' || c->map[y][x] == 'S' || \
			c->map[y][x] == 'W' || c->map[y][x] == 'E')
				return (init_player(y, x, c), c->map[y][x] = '0', NULL);
			x++;
		}
		y++;
	}
	return (NULL);
}

void	init_player(int y, int x, t_cub *c) //inicializa la dirección del jugador y su perpendicular, los valores no mencionados permanecen en cero
{
	c->p_y = (double)y * (double)CELL_HEIGHT; //posición inicial
	c->p_x = (double)x * (double)CELL_WIDHT;
	if (c->map[y][x] == 'N')
	{
		c->p_angle = PI / 2; //angulo en multiplos de PI
		c->p_angle_y = -1;
	}
	if (c->map[y][x] == 'W')
	{
		c->p_angle = PI;
		c->p_angle_x = -1;
	}
	if (c->map[y][x] == 'S')
	{
		c->p_angle = PI * 3 / 4;
		c->p_angle_y = 1;
	}
	if (c->map[y][x] == 'E')
	{
		c->p_angle = 2 * PI; //equivalente a 360 grados, se reinicia a cero
		c->p_angle_x = 1;
	}
	c->camera_x = c->p_angle_y * FIELD_OF_VIEW; //los ejes de la camara, son tangentes a los ejes del angulo del jugador, el valor de la tangente de un angulo de 60 grados es más o menos 0.66 (FOV, estático)
	c->camera_y = c->p_angle_x * FIELD_OF_VIEW;
}
