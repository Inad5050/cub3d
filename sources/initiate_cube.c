/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_cube.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:24:06 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/12 21:08:58 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//mlx_init(int32_t width, int32_t height, const char* title, bool resize);

void	initiate_cube(char **argv, t_cube *c)
{
	c->mlx = mlx_init(500, 500, "SUPER CUB3D", 1);
	if (!c->mlx)
		c_error("Error in mlx_init");
	
	c->map = read_map(argv[6], c);
	
	c->time = mlx_get_time();

	c->png_floor = ft_strdup("./texture/xpm/floor.xpm");
	if (!c->png_floor)
		c_error("Couldn't alloc in initiate_cube");
	c->png_wall = ft_strdup("./texture/xpm/wall.xpm");
	if (!c->png_wall)
		c_error("Couldn't alloc in initiate_cube");

}

void	read_map(char *map, t_cube *c);


