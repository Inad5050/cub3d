/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:04:14 by otboumeh          #+#    #+#             */
/*   Updated: 2025/02/19 18:27:06 by otboumeh         ###   ########.fr       */
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

int	verification_start(t_cube *cube, \
		t_player_position *player_position, char **argv)
{
	if (read_file(argv[1], cube) == 1)
		return (1);
	delete_tab(&cube->map, -1);
	if (last_verification(cube, player_position))
		return (1);
	return (0);
}
