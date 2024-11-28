/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:54:40 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/28 17:32:44 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	delete_tab(char ***map, int i)
{
	int		j;
	char	*new_line;
	char	*tmp;
	char	*to_append;

	while ((*map)[++i])
	{	
		if (*map == NULL || (*map)[i] == NULL)
    		return;
		new_line = ft_strdup("");
		j = -1;
		while ((*map)[i][++j])
		{
			if ((*map)[i][j] == '\t')
				to_append = ft_strdup("    ");
			else
				to_append = ft_sprintf("%c", (*map)[i][j]);
			tmp = ft_strdup(new_line);
			free(new_line);
			new_line = ft_sprintf("%s%s", tmp, to_append);
			free(tmp);
			free(to_append);
		}
		free((*map)[i]);
		(*map)[i] = new_line;
	}
}
int	last_verification(t_cube *cube, t_player_position *player_position)
{
	if (validate_file(cube))
	{
		free_content(cube);
		return (printf("Invalid input. Cleanup and exit\n"), 1);
	}
	if (validate_map(cube, player_position))
	{
		free_content(cube);
		return (printf("Invalid map. Cleanup and exit\n"), 1);
	}
	return (0);
}
int	validate_file(t_cube *cube)
{
	if (!cube->north_texture || !cube->south_texture
		|| !cube->west_texture || !cube->east_texture)
		return (ft_printf("Missing texture\n"), 1);
	if (cube->floor_color[0] < 0 || cube->floor_color[1] < 0
		|| cube->floor_color[2] < 0)
		return (ft_printf("Invalid floor color\n"), 1);
	if (cube->ceiling_color[0] < 0 || cube->ceiling_color[1] < 0
		|| cube->ceiling_color[2] < 0)
		return (ft_printf("Invalid ceiling color\n"), 1);
	if (!cube->map)
		return (ft_printf("Missing map\n"), 1);
	return (0);
}
