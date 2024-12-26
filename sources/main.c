/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/12/26 19:12:33 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_cub	*c;

/* 	if (parser(argc, argv))
		return (EXIT_FAILURE); */ //PARTE OTMAN
		
	c = ft_calloc(1, sizeof(t_cub)); //inicializa estructura
	if (!c)
		return (ft_printf("Couldn`t alloc t_cube c"), EXIT_FAILURE);
	map_read(argv, c); //lee el mapa
	initiate_mlx(c); //inicializa MLX
	image_load(c); //inicializa las imagenes
	map_render(c); //renderiza el mapa
	loops(c); //crea los loops (ESCP, player movement)
	free_memory(c); //libera toda la memoria alojada en el heap

	argc++;
	
	return (EXIT_SUCCESS);
}
