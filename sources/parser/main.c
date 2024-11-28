/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:04:14 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/28 17:39:43 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	check_arg_number(int argc)
{
	if (argc != 2)
	{
		printf("\n Invalid arguments number\n");
		exit(1);
	}
}
int	verification_start(t_cube *cube,\
		t_player_position *player_position, char **argv)
{
	if(read_file(argv[1], cube) == 1)
		return (1);
	delete_tab(&cube->map, -1);
	if (last_verification(cube, player_position))
		return (1);
	
	return (0); //LO PONGO PARA QUE COMPILE

}

int	parser(int argc, char **argv) //EL ANTIGUO MAIN
{
	t_cube	cube;
	t_player_position player_position;
	check_arg_number(argc);
	ft_bzero(&cube, sizeof(t_cube));
	check_extension(argv[1], &cube);
	if(verification_start(&cube, &player_position,argv))
		return(1);
	return (0);
}
