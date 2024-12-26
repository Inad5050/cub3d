/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:24:20 by dangonz3          #+#    #+#             */
/*   Updated: 2024/12/26 17:54:16 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	initiate_mlx(t_cub *c) //inicializa MLX
{
	map_axis_x(c);	
	c->mlx = mlx_init(c->map_axis_x * IMG_WIDHT, c->map_axis_y * IMG_HEIGHT, \
	"SUPER CUB3D", true);
	if (!c->mlx)
		c_error("Error in mlx_init", c);	
}

void	map_axis_x(t_cub *c) //consigue la dimension maxima del mapa sobre el eje x
{
	int	i;

	i = 0;
	while (i < c->map_axis_y - 1)
	{
		if ((int)ft_strlen(c->map[i]) > c->map_axis_x)
			c->map_axis_x = (int)ft_strlen(c->map[i]);
		i++;
	}
}
