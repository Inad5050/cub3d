/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:42:54 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/31 16:18:35 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

float	normalize_angle(float angle) //hace que el angulo sea positivo y menor a 360 grados
{
	angle = remainder(angle, 2 * PI); //hace el equivalente a angle % 2PI, pero con decimales (float)
	if (angle < 0)
		angle = angle + 2 * PI; //si el angulo es negativo obtenemos el equivalente positivo sumandole 2PI que equivale a 360 grados
	return (angle);
}

uint32_t	get_color(uint8_t *ptr) //load_png almacena el valor del color de los pixeles en estructuras de 4 integers de 8 bytes. Queremos combinar esos numeros en uno solo de 32 bytes.
{
	uint32_t	b; //blue
	uint32_t	g; //green
	uint32_t	r; //red
	uint32_t	a; //alpha. opacidad (?)

	r = (uint32_t)*(ptr);
	g = (uint32_t)*(ptr + 1);
	b = (uint32_t)*(ptr + 2);
	a = (uint32_t)*(ptr + 3);
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

int	has_wall_at(t_cub *c, float x, float y) //detecta si la coordenada es suelo u otro elemento
{
	int		map_grid_index_x;
	int		map_grid_index_y;
	char	tile;

	map_grid_index_x = ((int)x / TILE_SIZE);
	map_grid_index_y = ((int)y / TILE_SIZE);
	if (map_grid_index_y < 0 || map_grid_index_y >= c->map_axis_y) //si empieza a dar seg_fault mira aqui
		return (0);
	if (map_grid_index_x < 0 || 
	map_grid_index_x >= (int)ft_strlen(c->map[map_grid_index_y]))
		return (0);
	tile = c->map[map_grid_index_y][map_grid_index_x];
	
	/* printf("x = %f y = %f map_grid_index_x = %d map_grid_index_y = %d (int)ft_strlen(game->map[map_grid_index_y] = %d tile = %c\n", x, y, map_grid_index_x, map_grid_index_y, (int)ft_strlen(c->map[map_grid_index_y]), tile); */
	
	return (tile != '0');
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))); //toerema de pitagoras	
}
