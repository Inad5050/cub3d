/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:55:16 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/21 17:56:12 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_player(t_cub *c)
{
	c->p_fov = (60 * PI / 180);
	c->p_turnspeed = ANGLE_ROTATION_SIZE * (PI / 180);
	c->p_turnspeed_original = c->p_turnspeed;
	c->p_walkspeed = TILE_SIZE / MOVESPEED_MOD;
	locate_player(c);
	init_doors(c);
}

int	locate_player(t_cub *c)
{
	int	y;
	int	x;

	y = 0;
	while (c->map[y])
	{
		x = 0;
		while (c->map[y][x])
		{
			if (c->map[y][x] == 'D')
				c->door_number++;
			if (c->map[y][x] == 'N' || c->map[y][x] == 'S' || \
			c->map[y][x] == 'W' || c->map[y][x] == 'E')
				return (set_player_position(y, x, c), c->map[y][x] = '0', 0);
			x++;
		}
		y++;
	}
	return (0);
}

void	set_player_position(int y, int x, t_cub *c)
{
	c->p_y = y * TILE_SIZE + TILE_SIZE / 2;
	c->p_x = x * TILE_SIZE + TILE_SIZE / 2;
	if (c->map[y][x] == 'N')
		c->p_rotationangle = normalize_angle(3 * PI / 2);
	if (c->map[y][x] == 'W')
		c->p_rotationangle = normalize_angle(PI);
	if (c->map[y][x] == 'S')
		c->p_rotationangle = normalize_angle(PI / 2);
	if (c->map[y][x] == 'E')
		c->p_rotationangle = normalize_angle(0);
}
