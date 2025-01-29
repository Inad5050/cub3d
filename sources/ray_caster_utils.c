/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:42:54 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/29 15:55:32 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

float	normalizeAngle(float angle) //hace que el angulo sea positivo y menor a 360 grados
{
	angle = remainder(angle, 2 * PI); //hace el equivalente a angle % 2PI, pero con decimales (float)
	if (angle < 0)
		angle = angle + 2 * PI; //si el angulo es negativo obtenemos el equivalente positivo sumandole 2PI que equivale a 360 grados
	return (angle);
}

/* float	normalize_angle(float angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
	{
		angle = 2 * PI + angle;
	}
	return (angle);
} */

int	mapHasWallAt(t_cub *c, float x, float y) //detecta si la coordenada es suelo u otro elemento
{
	int		map_grid_index_x;
	int		map_grid_index_y;
	char	tile;

	map_grid_index_x = ((int)x / TILE_SIZE);
	map_grid_index_y = ((int)y / TILE_SIZE);
	if (map_grid_index_y < 0 || map_grid_index_y >= c->map_axis_y) //si empieza a dar seg_fault mira aqui
		return (0);
	if (map_grid_index_x < 0 || map_grid_index_x >= c->map_axis_x)
		return (0);
	tile = c->map[map_grid_index_y][map_grid_index_x];
	return (tile != '0');
}

float	distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))); //toerema de pitagoras	
}
