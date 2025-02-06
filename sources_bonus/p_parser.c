/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:04:14 by otboumeh          #+#    #+#             */
/*   Updated: 2025/02/06 16:00:36 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

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
	if (read_file(argv[1], cube) == 1)
		return (1);
	delete_tab(&cube->map, -1);
	if (last_verification(cube, player_position))
		return (1);
	// reach_last_character(argv[1]);
	
	return (0);
}
// void reach_last_character(const char *file_path)
// {
//     int fd;
//     char *line;
//     char last_char = '\0';

// 	fd = open(file_path, O_RDONLY); 
//     while ((line = ft_get_next_line(fd)) != NULL)
//     {
//         if (line[0] != '\0')
//         {
//             last_char = line[0];
//             for (int i = 0; line[i] != '\0'; i++)
//             {
//                 last_char = line[i];
//             }
//         }
//         free(line);
//     }
//     if (last_char != '\0')
//     {
//         printf("Last character: %c\n", last_char);
//     }
//     close(fd);
// }
