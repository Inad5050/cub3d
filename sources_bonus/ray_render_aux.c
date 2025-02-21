/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:20:27 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/21 16:35:06 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	draw_wall_strip(t_cub *c, int x)
{
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		mlx_put_pixel(c->win_mlx3d, x, y, c->strip[y]);
		y++;
	}
}
