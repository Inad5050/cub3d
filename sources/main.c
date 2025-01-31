/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/31 16:13:51 by dangonz3         ###   ########.fr       */
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
	init_game(c); //inicializa el juego
	init_player(c); //inicializa las variables relativas al jugador
	mlx_image_to_window(c->mlx, c->win_mlx3D, 0, 0); //inicializa la ventana (que CODAM llama imagenes)
	mlx_loop_hook(c->mlx, game_loop, c); //añade game_loop() al loop que la mlx repetira durante la duracion del programa
	mlx_loop(c->mlx); //realiza los loops
	c_close(c); //cierra las ventanas y libera toda la memoria alojada en el heap
	return (EXIT_SUCCESS);
}

//actualiza el estado del juego cada 30 FPS (Frames Per Second)
void	game_loop(void *param)
{
	t_cub			*c;
	unsigned int	timenow;
	
	c = (t_cub *)param;
	timenow = mlx_get_time() * 1000; //el tiempo actual en segundos
	if (timenow - c->timelastframe > 1000 / FRAMES)
	{
		process_player_input(c); //actualiza el angulo y la posicion del jugador
		ray_caster(c); //lanza rayos
		/* ft_memset(c->win_mlx3D->pixels, 0, c->win_mlx3D->width * c->win_mlx3D->height * sizeof(unsigned int)); //resetea la ventana */
		ray_render(c); //renderiza el mapa 3D
		c->timelastframe = timenow; //actualiza la última vez que ejecutamos game_loop
	}
}
