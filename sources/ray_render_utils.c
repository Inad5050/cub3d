/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:26:02 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/24 17:23:02 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

float nor_angle(float angle) // normalize the angle
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > (2 * PI))
		angle -= (2 * PI);
	return (angle);
}

void my_mlx_pixel_put(t_cub *c, int x, int y, int color) // put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= WIN_WIDHT)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= WIN_HEIGHT)
		return ;
	mlx_pixel_put(c->mlx, c->win_mlx_3D, x, y, color); // put the pixel //ESTO ES CORRECTO?

	//mlx_put_pixel(mlx->img, x, y, color); // put the pixel
}
