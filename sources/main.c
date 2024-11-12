/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/12 20:36:48 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//void mlx_loop(mlx_t* mlx);

int	main(int argc, char **argv)
{
	t_cube	*c;
	
	c = ft_calloc(1, sizeof(t_cube));
	if (!c)
		return (1);

	initiate_cube(c);
		
	set_hooks(c);
	load_images(c);
	
	mlx_loop(c->mlx);
	free_memory(c);
	return (0);
}
