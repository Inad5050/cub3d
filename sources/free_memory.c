/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:21:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/15 19:43:32 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_memory(t_cube *c)
{
	mlx_close_window(c->mlx);
	mlx_terminate(c->mlx);
	
	//...
	
	free_img(c);
	if (c)
		free(c);
}

void	free_img(t_cube *c)
{
	if (c->texture_floor)
		mlx_delete_texture(c->texture_floor);
	if (c->png_floor)
		free(c->png_floor);
	if (c->texture_wall)
		mlx_delete_texture(c->texture_wall);
	if (c->png_wall)
		free(c->png_wall);

	//...

}
