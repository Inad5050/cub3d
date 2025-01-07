/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/07 15:05:16 by dangonz3         ###   ########.fr       */
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
	map_render(c); //renderiza el mapa	
	mlx_hook(c->win_mlx, ON_KEYDOWN, 1L << 0, key_hooks, (void *)c); //define los loops que el programa tendra que repetir
	mlx_hook(c->win_mlx, ON_DESTROY, 1L << 17, c_close, (void *)c);
	mlx_loop(c->mlx); //realiza los loops
	free_memory(c); //libera toda la memoria alojada en el heap

	argc++;
	
	return (EXIT_SUCCESS);
}
