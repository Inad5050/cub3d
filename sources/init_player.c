/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:55:16 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/30 15:47:22 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_player(t_cub *c)
{
	c->p_fov = (60 * PI / 180); //para un Field of View (FOV) de 60 grados. Siempre sera el mismo (aprox 1.66)
	c->p_turnspeed = ANGLE_ROTATION_SIZE * (PI / 180);
	c->p_walkspeed = TILE_SIZE / 10;	
	locate_player(c);	
}

int	locate_player(t_cub *c) //localiza la posición inicial del jugador y coloca suelo '0' en su lugar
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
				return (init_player_inmap(y, x, c), c->map[y][x] = '0', 0);
			x++;
		}
		y++;
	}
	return (0);
}

void	init_player_inmap(int y, int x, t_cub *c) //inicializa la dirección del jugador y su perpendicular, los valores no mencionados permanecen en cero
{
	c->p_y = y * TILE_SIZE + TILE_SIZE / 2; //posición inicial
	c->p_x = x * TILE_SIZE + TILE_SIZE / 2;
	if (c->map[y][x] == 'N')
	{
		c->p_rotationangle = normalize_angle(3 * PI / 2); //angulo en multiplos de PI
		c->player_direction = NORTH;
	}
	if (c->map[y][x] == 'W')
	{
		c->p_rotationangle = normalize_angle(PI);
		c->player_direction = WEST;
	}
	if (c->map[y][x] == 'S')
	{
		c->p_rotationangle = normalize_angle(PI / 2);
		c->player_direction = SOUTH;
	}
	if (c->map[y][x] == 'E')
	{
		c->p_rotationangle = normalize_angle(0); //equivalente a 360 grados, se reinicia a cer
		c->player_direction = EAST;  
	}
}
