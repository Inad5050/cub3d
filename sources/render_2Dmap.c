/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2Dmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:58:55 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/28 17:54:22 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* void	render_2Dmap(t_cub *c) //recorre la matriz del mapa
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
	player_print(c->p_y, c->p_x, c->player_img, c);
}

void	map_select_element(int y, int x, t_cub *c) //identifica cada elemento del mapa y lo imprime en la pantalla
{	
	if (c->map[y][x] == '0')
		map_print(y, x, c->floor, c);
	else if (c->map[y][x] == '1')
		map_print(y, x, c->wall_n, c);
}

void	map_print(int y, int x, t_img *c_img, t_cub *c) //hace que sea más fácil llamar a mlx_put_image_to_window
{	
	mlx_put_image_to_window(c->mlx, c->win_mlx2D, c_img->img_ptr, x * CELL_WIDHT, y * CELL_HEIGHT);
}

void	player_print(double y, double x, t_img *c_player_img, t_cub *c) //imprime al jugador en pantalla
{	
	mlx_put_image_to_window(c->mlx, c->win_mlx2D, c_player_img->img_ptr, (int)x, (int)y);
} */
