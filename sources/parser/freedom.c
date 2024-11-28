/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:28:55 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/28 17:32:34 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* free the selected line and print a error message */
void	free_line(char *line, t_cube *cube)
{
	printf("Error parsing; wrong content\n");
	free(line);
	free_content(cube);
	exit(1);
}
/* free the game (map,textures and colors) */
void	free_content(t_cube *cube)
{
	int	i;

	i = 0;
	if (cube->north_texture)
		free(cube->north_texture);
	if (cube->south_texture)
		free(cube->south_texture);
	if (cube->west_texture)
		free(cube->west_texture);
	if (cube->east_texture)
		free(cube->east_texture);
	if (cube->map)
	{
		while (cube->map[i])
		{
			free(cube->map[i]);
			i++;
		}
		free(cube->map);
	}
	printf("CLosing program");
}
/* Function to free arrays */
void	array_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}