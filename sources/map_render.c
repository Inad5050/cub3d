/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:58:55 by dangonz3          #+#    #+#             */
/*   Updated: 2024/12/30 21:08:25 by dangonz3         ###   ########.fr       */
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
}

void	map_select_element(int y, int x, t_cub *c) //identifica cada elemento del mapa y lo imprime en la pantalla
{	
	if (c->map[y][x] == '0')
		map_print(y, x, c->floor, c);
	else if (c->map[y][x] == '1')
	{
		if (c->map[y][x] == 'N') //tenemos que determinar que pared está mirando
			map_print(y, x, c->wall_n, c);
		else if (c->map[y][x] == 'S')
			map_print(y, x, c->wall_s, c);
		else if (c->map[y][x] == 'W')
			map_print(y, x, c->wall_w, c);
		else if (c->map[y][x] == 'E')
			map_print(y, x, c->wall_e, c);
	}
}

void	map_print(int y, int x, t_img *c_img, t_cub *c) //identifica cada elemento del mapa y lo imprime en la pantalla
{	
	if (mlx_put_image_to_window(c->mlx, c->win, c_img->img_ptr, x * IMG_WIDHT, y * IMG_HEIGHT) < 1)
		c_error("Couldn't image_print", c);
}