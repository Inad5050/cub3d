/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/12 20:04:25 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//void mlx_loop(mlx_t* mlx);

int	main(int argc, char **argv)
{
	t_cube	*c;
	
	if (!initiate_cube(c))
		return (1);
		
	set_hooks(c);
	load_images(c);
	
	mlx_loop(c->mlx);
	free_memory(c);
	return (0);
}
