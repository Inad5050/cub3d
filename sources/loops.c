/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:44:08 by dangonz3          #+#    #+#             */
/*   Updated: 2024/12/30 21:10:03 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	loops(t_cub *c)
{
	/* mlx_loop_hook(c->mlx, key_hooks, c); */ //define los loops que el programa tendra que repetir

	//...

	mlx_loop(c->mlx); //realiza los loops
}

/* void	key_hooks(void *c_void)
{
	t_cub *c;

	c = c_void;	
	if (mlx_is_key_down(c->mlx, MLX_KEY_ESCAPE)) //si se presiona ESCAPE cierra el programa
	{
		free_memory(c);
		exit(EXIT_FAILURE);
	}
	// player_move(c); 
	// map_render(c);
	
	//...

} */
