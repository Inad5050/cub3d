/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_util_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:54:40 by otboumeh          #+#    #+#             */
/*   Updated: 2025/02/21 13:10:19 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static char	*replace_tabs(char *line)
{
	int		j;
	char	*new_line;
	char	*tmp;
	char	*to_append;

	new_line = ft_strdup("");
	j = -1;
	while (line[++j])
	{
		if (line[j] == '\t')
			to_append = ft_strdup("    ");
		else
			to_append = ft_sprintf("%c", line[j]);
		tmp = ft_strdup(new_line);
		free(new_line);
		new_line = ft_sprintf("%s%s", tmp, to_append);
		free(tmp);
		free(to_append);
	}
	return (new_line);
}

void	delete_tab(char ***map, int i)
{
	char	*tmp;

	while ((*map)[++i])
	{
		if (*map == NULL || (*map)[i] == NULL)
			return ;
		tmp = (*map)[i];
		(*map)[i] = replace_tabs((*map)[i]);
		free(tmp);
	}
}

int	last_verification(t_parse *cube, t_player_position *player_position)
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

int	validate_file(t_parse *cube)
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
