/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/28 19:48:25 by dangonz3         ###   ########.fr       */
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
	init_3D(c); //inicializa el ray caster
	/* mlx_loop_hook(c->mlx, key_hook, c); */ //define los loops que el programa tendra que repetir
	mlx_loop_hook(c->mlx, render_maps, c); //lanza rayos
	mlx_loop(c->mlx); //realiza los loops
	c_close(c); //cierra las ventanas y libera toda la memoria alojada en el heap
	return (EXIT_SUCCESS);
}

void	render_maps(void *param)
{
	t_cub			*c;
	unsigned int	timenow;
	
	c = (t_cub *)param;
	timenow = mlx_get_time() * 1000;
	if (timenow - c->timelastframe > 1000 / FRAMES)
	{
		key_hook(c);
		ray_caster(c);
		ray_render(c);
		c->timelastframe = timenow;
	}
}