/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:58:55 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/07 19:35:41 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	map_render(t_cub *c) //recorre la matriz del mapa
{
	int	y;
	int	x;

	y = 0;
	while (c->map[y])
	{
		x = 0;
		while (c->map[y][x])
			map_select_element(y, x++, c);
		y++;
	}
	player_print(c->p->p_y, c->p->p_x, c->player_img, c);
}

void	map_select_element(int y, int x, t_cub *c) //identifica cada elemento del mapa y lo imprime en la pantalla
{	
	locate_player(y, x, c);
	if (c->map[y][x] == '0')
		map_print(y, x, c->floor, c);
	else if (c->map[y][x] == '1')
		map_print(y, x, c->wall_n, c);
}

void	map_print(int y, int x, t_img *c_img, t_cub *c) //hace que sea más fácil llamar a mlx_put_image_to_window
{	
	mlx_put_image_to_window(c->mlx, c->win_mlx, c_img->img_ptr, x * IMG_WIDHT, y * IMG_HEIGHT);
}

void	player_print(double y, double x, t_img *c_img, t_cub *c) //si ya hemos localizado al jugador lo imprime en la pantalla, imprime entre casillas
{	
	if (!(c->p->p_y) && !(c->p->p_x))
		return;
	mlx_put_image_to_window(c->mlx, c->win_mlx, c_img->img_ptr, (int)x, (int)y);
}

void	locate_player(int y, int x, t_cub *c) //localiza la posicion inicial del jugador y la sustituye por suelo '0'
{
	if ((c->p->p_y) || (c->p->p_x))
		return;
	if (!(c->map[y][x] == 'N' || c->map[y][x] == 'S' || \
	c->map[y][x] == 'W' || c->map[y][x] == 'E'))
		return;
	c->p->p_y = (double)y * (double)IMG_HEIGHT;
	c->p->p_x = (double)x * (double)IMG_WIDHT;
	c->map[y][x] = '0';
}
