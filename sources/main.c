/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/24 17:18:25 by dangonz3         ###   ########.fr       */
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
	argc++; //borrar luego

	init_map(argv, c); //lee el mapa
	init_game(c); //inicializa estructuras e imagenes
	/* render_maps(c);  *///renderiza el mapa 2D y las imagenes 3D
	init_3D(c); //inicializa el ray caster
	mlx_hook(c->win_mlx_2D, ON_KEYDOWN, 1L << 0, key_hooks, c); //define los loops que el programa tendra que repetir
	mlx_hook(c->win_mlx_2D, ON_DESTROY, 1L << 17, (void *)c_close, c); //cierra la ventana 2D si pulsamos la cruz
	mlx_hook(c->win_mlx_3D, ON_DESTROY, 1L << 17, (void *)c_close, c); //cierra la ventana 3D si pulsamos la cruz
	mlx_loop_hook(c->mlx, (void *)render_maps, c); //lanza rayos
	mlx_loop(c->mlx); //realiza los loops
	c_close(c); //cierra las ventanas y libera toda la memoria alojada en el heap
	return (EXIT_SUCCESS);
}

void	render_maps(t_cub *c)
{
	ray_caster(c);
	render_2Dmap(c);
}