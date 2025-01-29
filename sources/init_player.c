/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:55:16 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/29 15:56:12 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
		c->p_rotationangle = normalizeAngle(3 * PI / 2); //angulo en multiplos de PI
		c->player_direction = NORTH;
	}
	if (c->map[y][x] == 'W')
	{
		c->p_rotationangle = normalizeAngle(PI);
		c->player_direction = WEST;
	}
	if (c->map[y][x] == 'S')
	{
		c->p_rotationangle = normalizeAngle(PI / 2);
		c->player_direction = SOUTH;
	}
	if (c->map[y][x] == 'E')
	{
		c->p_rotationangle = normalizeAngle(0); //equivalente a 360 grados, se reinicia a cer
		c->player_direction = EAST;  
	}
}
