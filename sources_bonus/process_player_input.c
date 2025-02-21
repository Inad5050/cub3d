/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_player_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:44:08 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/21 16:26:06 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	mlx_cursor_hook(mlx_t *mlx, mlx_cursorfunc func, void *param);
void	mlx_get_mouse_pos(mlx_t *mlx, int32_t *x, int32_t *y);

void	process_player_input(void *param)
{
	t_cub	*c;

	c = (t_cub *)param;
	c->p_walkdirection = 0;
	c->p_strafedirection = 0;
	c->p_turndirection = 0;
	c->p_turnspeed = c->p_turnspeed_original;
	if (mlx_is_key_down(c->mlx, MLX_KEY_ESCAPE))
		c_close(c);
	if (mlx_is_key_down(c->mlx, MLX_KEY_W))
		c->p_walkdirection = 1;
	if (mlx_is_key_down(c->mlx, MLX_KEY_S))
		c->p_walkdirection = -1;
	if (mlx_is_key_down(c->mlx, MLX_KEY_A))
		c->p_strafedirection = -1;
	if (mlx_is_key_down(c->mlx, MLX_KEY_D))
		c->p_strafedirection = 1;
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT))
		c->p_turndirection = -1;
	if (mlx_is_key_down(c->mlx, MLX_KEY_RIGHT))
		c->p_turndirection = 1;
	mouse_hook(c);
	update_player_position(c);
	open_doors(c);
}

void	mouse_hook(t_cub *c)
{
	int32_t	x;
	int32_t	y;

	if (c->p_turndirection)
		return ;
	mlx_get_mouse_pos(c->mlx, &x, &y);
	if (y < 0 || WIN_HEIGHT <= y)
		return ;
	if (0 < x && x <= WIN_WIDTH * 0.45)
	{
		c->p_turndirection = -1;
		if (WIN_WIDTH * 0.3 < x && x <= WIN_WIDTH * 0.45)
			c->p_turnspeed *= 0.2;
		if (WIN_WIDTH * 0.15 < x && x <= WIN_WIDTH * 0.3)
			c->p_turnspeed *= 0.4;
	}
	if (WIN_WIDTH * 0.55 < x && x < WIN_WIDTH)
	{
		c->p_turndirection = 1;
		if (WIN_WIDTH * 0.55 < x && x <= WIN_WIDTH * 0.7)
			c->p_turnspeed *= 0.2;
		if (WIN_WIDTH * 0.7 < x && x <= WIN_WIDTH * 0.85)
			c->p_turnspeed *= 0.4;
	}
}

void	update_player_position(t_cub *c)
{
	float	movestep;
	float	strafestep;
	float	new_p_x;
	float	new_p_y;

	c->p_rotationangle = normalize_angle(c->p_rotationangle + \
	c->p_turndirection * c->p_turnspeed);
	movestep = c->p_walkdirection * c->p_walkspeed;
	strafestep = c->p_strafedirection * c->p_walkspeed;
	new_p_x = c->p_x + cos(c->p_rotationangle) * movestep + \
	cos(c->p_rotationangle + PI / 2) * strafestep;
	new_p_y = c->p_y + sin(c->p_rotationangle) * movestep + \
	sin(c->p_rotationangle + PI / 2) * strafestep;
	if (!check_wall_collision(c, new_p_x, c->p_y) && \
		!check_wall_collision(c, new_p_x - c->p_walkdirection * \
			PLAYER_SIZE / 2, c->p_y))
		c->p_x = new_p_x;
	if (!check_wall_collision(c, c->p_x, new_p_y) && \
	!check_wall_collision(c, c->p_x, new_p_y - c->p_strafedirection * \
		PLAYER_SIZE / 2))
		c->p_y = new_p_y;
}

int	check_wall_collision(t_cub *c, float new_x, float new_y)
{
	int		map_x;
	int		map_y;
	int		offset_x;
	int		offset_y;

	offset_y = -1;
	while (offset_y <= 1)
	{
		offset_x = -1;
		while (offset_x <= 1)
		{
			map_x = ((int)(new_x + offset_x * 0.1) / TILE_SIZE);
			map_y = ((int)(new_y + offset_y * 0.1) / TILE_SIZE);
			if (map_y >= 0 && map_x >= 0 && map_y < c->map_max_y && \
			map_x < (int)ft_strlen(c->map[map_y]))
			{
				if (c->map[map_y][map_x] != '0' || c->door_closing)
					return (1);
			}
			offset_x++;
		}
		offset_y++;
	}
	return (0);
}
