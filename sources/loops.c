/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:44:08 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/14 22:28:51 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	loops(t_cube *c)
{
	/* mlx_loop_hook(c->mlx, (void (*)(void *))key_hooks, c->mlx); */

	//...

	mlx_loop(c->mlx);
}

void	key_hooks(t_cube *c)
{
	if (mlx_is_key_down(c->mlx, MLX_KEY_ESCAPE))
		free_memory(c);
	if (mlx_is_key_down(c->mlx, MLX_KEY_UP))
		c->player_x -= 5;
	if (mlx_is_key_down(c->mlx, MLX_KEY_DOWN))
		c->player_x += 5;
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT))
		c->player_y -= 5;
	if (mlx_is_key_down(c->mlx, MLX_KEY_RIGHT))
		c->player_y += 5;
	
	//...
	
}
