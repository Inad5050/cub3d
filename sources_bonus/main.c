/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:23 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/21 17:56:15 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	main(int argc, char **argv)
{
	t_parse				cube;
	t_player_position	player_position;
	t_cub				*c;

	check_arg_number(argc);
	ft_bzero(&cube, sizeof(t_parse));
	check_extension(argv[1]);
	if (verification_start(&cube, &player_position, argv))
		return (1);
	c = ft_calloc(1, sizeof(t_cub));
	if (!c)
		return (ft_printf("Couldn`t alloc c"), EXIT_FAILURE);
	c->parse_struct = &cube;
	init_game(c, );
	init_player(c);
	mlx_image_to_window(c->mlx, c->win_mlx3d, 0, 0);
	mlx_loop_hook(c->mlx, game_loop, c);
	mlx_loop(c->mlx);
	c_close(c);
	return (EXIT_SUCCESS);
}

void	game_loop(void *param)
{
	t_cub			*c;
	unsigned int	timenow;

	c = (t_cub *)param;
	timenow = mlx_get_time() * 1000;
	if (timenow - c->timelastframe > 1000 / FRAMES)
	{
		process_player_input(c);
		ray_caster(c);
		ray_render(c);
		minimap_render(c);
		update_doors(c);
		c->timelastframe = timenow;
	}
}
