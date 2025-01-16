/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/15 15:34:47 by dangonz3         ###   ########.fr       */
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

	map_read(argv, c); //lee el mapa
	init_game(c); //inicializa estructuras e imagenes
	init_3D(c);
	map_render(c); //renderiza el mapa 2D
	/* ray_direction(c); */ //renderiza el mapa 3D
	mlx_hook(c->win_mlx_2D, ON_KEYDOWN, 1L << 0, key_hooks, (void *)c); //define los loops que el programa tendra que repetir
	mlx_hook(c->win_mlx_2D, ON_DESTROY, 1L << 17, c_close, (void *)c);
	mlx_hook(c->win_mlx_3D, ON_DESTROY, 1L << 17, c_close, (void *)c);
	mlx_loop(c->mlx); //realiza los loops
	free_memory(c); //libera toda la memoria alojada en el heap

	argc++;
	
	return (EXIT_SUCCESS);
}
