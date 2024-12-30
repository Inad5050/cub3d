/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/12/30 21:09:36 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_cub	*c;
	
	c = ft_calloc(1, sizeof(t_cub)); 
	if (!c)
		return (ft_printf("Couldn`t alloc c"), EXIT_FAILURE);

	//PARSING

	init_game(c); //inicializa estructuras e imagenes
	map_read(argv, c); //lee el mapa
	map_render(c); //renderiza el mapa	
	loops(c); //crea los loops (ESCP, player movement)
	free_memory(c); //libera toda la memoria alojada en el heap

	argc++;
	
	return (EXIT_SUCCESS);
}
