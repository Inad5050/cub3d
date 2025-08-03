/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_freedom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:28:55 by otboumeh          #+#    #+#             */
/*   Updated: 2025/02/19 18:25:15 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	free_line(char *line, t_parse *cube)
{
	printf("Error parsing; wrong content\n");
	free(line);
	free_content(cube);
	printf("CLosing program\n");
	exit(1);
}

void	free_content(t_parse *cube)
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
}

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
