/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:21:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/12 20:30:39 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_memory(t_cube *c)
{
	if (c->mlx)
		free(c->mlx);
	if (c)
		free(c);
	
	free_img(c);
}

//void mlx_delete_texture(mlx_texture_t* texture);

void	free_img(t_cube *c)
{
	if (c->img_floor)
		mlx_delete_texture(c->img_floor);
	if (c->img_roof)
		mlx_delete_texture(c->img_roof);

	
}
