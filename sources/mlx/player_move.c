/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:17:26 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/28 17:34:12 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	player_move(t_cub *c)
{
	if (mlx_is_key_down(c->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(c->mlx, MLX_KEY_D))
		move(c, 1);
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT) || mlx_is_key_down(c->mlx, MLX_KEY_A))
		move(c, 2);
	if (mlx_is_key_down(c->mlx, MLX_KEY_DOWN) || mlx_is_key_down(c->mlx, MLX_KEY_S))
		move(c, 3);
	if (mlx_is_key_down(c->mlx, MLX_KEY_UP) || mlx_is_key_down(c->mlx, MLX_KEY_W))
		move(c, 4);
	c->map[c->player_y][c->player_x] = 'N';
}

void 	move(t_cub *c, int n)
{
	if (n == 1 && c->map[c->player_y][c->player_x + 1] == '0')
	{
		c->map[c->player_y][c->player_x] = '0';
		c->player_x = c->player_x + 1;
	}
	if (n == 2 && c->map[c->player_y][c->player_x + 1]  == '0')
	{
		c->map[c->player_y][c->player_x] = '0';
		c->player_x = c->player_x - 1;
	}
	if (n == 3 && c->map[c->player_y + 1][c->player_x]  == '0')
	{
		c->map[c->player_y][c->player_x] = '0';
		c->player_y = c->player_y + 1;
	}
	if (n == 4 && c->map[c->player_y - 1][c->player_x]  == '0')
	{
		c->map[c->player_y][c->player_x] = '0';
		c->player_y = c->player_y - 1;
	}
}
