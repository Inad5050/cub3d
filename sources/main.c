/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/27 19:34:35 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//void mlx_loop(mlx_t* mlx);

int	main(int argc, char **argv)
{
	t_cube	*c;

	if (argc != 2)
		return (ft_printf("I need a map!\n"), EXIT_FAILURE);
	c = ft_calloc(1, sizeof(t_cube));
	if (!c)
		return (ft_printf("Couldn`t alloc t_cube c"), EXIT_FAILURE);
	map_read(argv, c);
	initiate_mlx(c);	
	image_load(c);
	map_render(c);
	loops(c);
	free_memory(c);
	return (EXIT_SUCCESS);
}
