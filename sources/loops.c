/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:44:08 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/27 19:58:24 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	loops(t_cube *c)
{
	mlx_loop_hook(c->mlx, key_hooks, c);

	//...

	mlx_loop(c->mlx);
}

void	key_hooks(void *c_void)
{
	t_cube *c;

	c = c_void;	
	if (mlx_is_key_down(c->mlx, MLX_KEY_ESCAPE))
	{
		free_memory(c);
		exit(EXIT_FAILURE);
	}
	player_move(c);
	map_render(c);
	
	//...

}
