/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:24:06 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/12 20:02:30 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//mlx_init(int32_t width, int32_t height, const char* title, bool resize);

void	initiate_cube(t_cube *c)
{
	c = ft_calloc(1, sizeof(t_cube));
	if (!c)
		c_error("Error in mlx_init");
	c->mlx = mlx_init(500, 500, "SUPER CUB3D", 1);
	if (!c->mlx)
		c_error("Error in mlx_init");
		
	c->time = mlx_get_time();


}