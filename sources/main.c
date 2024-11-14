/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/14 22:16:16 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//void mlx_loop(mlx_t* mlx);

int	main(int argc, char **argv)
{
	t_cube	*c;
	
	c = initiate_cube(argv);
	
	image_load(c);
	
	loops(c);
	
	free_memory(c);

/* 	mlx_loop(c->mlx);
	free_memory(c);*/

	(void)argc; 

	return (EXIT_SUCCESS);
}
