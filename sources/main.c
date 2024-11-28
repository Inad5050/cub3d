/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/28 18:00:46 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_cub	*c;

/* 	if (parser(argc, argv))
		return (EXIT_FAILURE); */
	c = ft_calloc(1, sizeof(t_cub));
	if (!c)
		return (ft_printf("Couldn`t alloc t_cube c"), EXIT_FAILURE);
	map_read(argv, c);
	initiate_mlx(c);
	image_load(c);
	map_render(c);
	loops(c);
	free_memory(c);

	argc++;
	
	return (EXIT_SUCCESS);
}
