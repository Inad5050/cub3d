/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:04:02 by dani              #+#    #+#             */
/*   Updated: 2025/01/15 13:50:42 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	render_3Dmap(t_cub *c)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDHT)
			select_3Dmap(y, x++, c);
		y++;
	}
}

void	select_3Dmap(int y, int x, t_cub *c)
{
	if (c->map_3D[y][x] == FLOOR)
		print_3Dmap(y, x, PURPLE, c);
	else if (c->map_3D[y][x] == WALL)
		print_3Dmap(y, x, BLUE, c);
	else if (c->map_3D[y][x] == CEILLING)
		print_3Dmap(y, x, WHITE, c);
}

void	print_3Dmap(int y, int x, int color, t_cub *c)
{
	mlx_pixel_put(c->mlx, c->win_mlx_3D, x, y, color);
}