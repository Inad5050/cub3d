/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:40:13 by otboumeh          #+#    #+#             */
/*   Updated: 2025/02/21 12:25:24 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	perror_neighbour(char *line, char *neighbour)
{
	printf("Invalid map line. Not closed:\n\t%s\n\t%s <-\n", line, neighbour);
}

int	validate_top_bottom(char *line)
{
	int	idx;

	idx = -1;
	while (line[++idx] && line[idx] != '\n')
	{
		if (!(line[idx] == ' ' || line[idx] == '1'))
			return (ft_printf("Invalid map top || bottom:\n\t%s\n", line), 1);
	}
	return (0);
}

int	validate_neighbors(char **map, int x, int y)
{
	int	map_len;
	int	line_len;

	map_len = array_len(map);
	line_len = (int)ft_strlen(map[y]);
	if (map[y][x] && ft_strchr("0NSWE", map[y][x]))
	{
		if (y > 0 && (int)ft_strlen(map[y - 1]) - 1 < x)
			return (perror_neighbour(map[y - 1], map[y]), 1);
		if (x > 0 && map[y][x - 1] == '\0')
			return (printf("Invalid map line. Not closed:\n\t%s\n", map[y]), 1);
		if (y < map_len - 1 && (int)ft_strlen(map[y + 1]) - 1 < x)
			return (perror_neighbour(map[y], map[y + 1]), 1);
		if (x < line_len - 1 && map[y][x + 1] == '\0')
			return (printf("Invalid map line: %s\n", map[y]), 1);
		if (y > 0 && map[y - 1][x] && map[y - 1][x] == ' ')
			return (perror_neighbour(map[y - 1], map[y]), 1);
		if (x > 0 && map[y][x - 1] && map[y][x - 1] == ' ')
			return (printf("Invalid map line. Not closed:\n\t%s\n", map[y]), 1);
		if (y < map_len - 1 && map[y + 1][x] && map[y + 1][x] == ' ')
			return (perror_neighbour(map[y], map[y + 1]), 1);
		if (x < line_len - 1 && map[y][x + 1] && map[y][x + 1] == ' ')
			return (printf("Invalid map line: %s\n", map[y]), 1);
	}
	return (0);
}

static int	validate_line(char **map, int x, int y,
t_player_position *player_position)
{
	char	*line;

	player_position->orientation = 0;
	line = map[y];
	while (line[++x] && space_verification(line[x]))
		;
	if (line[x] != '1' || line[ft_strlen(line) - 1] != '1')
		return (ft_printf("Invalid map line:\n\t%s\n", line), 1);
	while (line[++x])
	{
		if (!ft_strchr(" 01MD", line[x]))
		{
			if (ft_strchr("NSWE", line[x]))
			{
				if (player_position->orientation)
					return (ft_printf("Multiple start positions\n"), 1);
				set_initial_position(player_position, x, y, line[x]);
			}
			else
				return (ft_printf("Invalid map line:\n\t%s\n", line), 1);
		}
		if (validate_neighbors(map, x, y))
			return (1);
	}
	return (0);
}

int	validate_map(t_parse *cube_data, t_player_position *player_position)
{
	int	idx;
	int	max_y_size;

	max_y_size = array_len(cube_data->map);
	player_position->x = -1;
	player_position->y = -1;
	if (max_y_size <= 0)
		return (ft_printf("Invalid map y\n"), 1);
	idx = -1;
	while (cube_data->map[++idx])
	{
		if (ft_strlen(cube_data->map[idx]) <= 0)
			return (ft_printf("Invalid map x\n Cube data map[%s] with idex %d",
					cube_data->map[idx], idx), 1);
		if ((idx == 0 || idx == max_y_size - 1)
			&& validate_top_bottom(cube_data->map[idx]))
			return (1);
		if (validate_line(cube_data->map, -1, idx, player_position))
			return (1);
	}
	if (player_position->x == -1 || player_position->y == -1)
		return (ft_printf("No start position\n"), 1);
	return (0);
}
