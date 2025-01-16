/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:11:46 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/15 16:11:50 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	init_3D(t_cub *c)
{
	c->map_3D = ft_calloc(WIN_HEIGHT * WIN_WIDHT, sizeof(char));
	if (!c->map_3D)
		return (c_error("Couldn't initiate c->map3D", c), EXIT_FAILURE);
	c->rays = ft_calloc(WIN_WIDHT, sizeof(t_ray));
	if (!c->rays)
		return (c_error("Couldn't initiate c->rays", c), EXIT_FAILURE);	
	return (0);
}
