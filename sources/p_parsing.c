/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:47:40 by otboumeh          #+#    #+#             */
/*   Updated: 2025/02/03 14:40:27 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* This function delete the unecessary white spaces founded in the line and
return a clean line*/
char	*line_verification(char *line)
{
	int		i;
	char	*tmp;
	char	*content;
	
	if(!line)
		return NULL;
	i = 3;
	while (line[i])
	{
		if (!space_verification(line[i]))
			break ;
		i++;
	}
	tmp = ft_substr(line, i, ft_strlen(line) - i);
	if(!tmp)
		return (NULL);
	content = ft_strtrim(tmp, "\n");
	if(!content)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (content);
}
/* this function parses a line of text representing RGB color values 
 into an integer array color[3]. It performs validation to ensure the values are within the RGB range (0-255)*/
int	parse_colors(char *line, int color[3])
{
	char	*tmp;
	char	**colors;
	int		i;

	tmp = ft_strtrim(line, " ");
	printf("%s\n",tmp);
	colors = ft_split(tmp, ',');
	free(tmp);
	if (array_len(colors) != 3)
	{
		array_free(colors);
		return (1);
	}
	i = -1;
	while (++i < 3)
	{
		if (!is_number(colors[i]))
			return (array_free(colors), 1);
		color[i] = ft_atoi(colors[i]);
		if (color[i] < 0 || color[i] > 255)
			return (array_free(colors), 1);
		printf("color[%d]: %d\n", i, color[i]);
	}
	array_free(colors);
	return (0);
}
/* This function verify line per line to verify the existance of the structure and send the information 
to the correspendent function if all struct is found start analizing the map if the variable flag is 
positif free the program */
static int	parse_texture_or_color(char *line, char *trimmed_line, t_cube *cube)
{
	if (ft_strncmp("NO ", trimmed_line, 3) == 0)
		cube->north_texture = line_verification(trimmed_line);
	else if (ft_strncmp("SO ", trimmed_line, 3) == 0)
		cube->south_texture = line_verification(trimmed_line);
	else if (ft_strncmp("WE ", trimmed_line, 3) == 0)
		cube->west_texture = line_verification(trimmed_line);
	else if (ft_strncmp("EA ", trimmed_line, 3) == 0)
		cube->east_texture = line_verification(trimmed_line);
	else if (ft_strncmp("F ", trimmed_line, 2) == 0)
		return (parse_colors(trimmed_line + 1, cube->floor_color));
	else if (ft_strncmp("C ", trimmed_line, 2) == 0)
		return (parse_colors(trimmed_line + 1, cube->ceiling_color));
	else
		parse_map(line, cube);
	return (0);
}

int	parse_line(char *line, t_cube *cube)
{
	int		flag;
	char	*trimmed_line;

	if (!line)
		return (1);
	trimmed_line = ft_strtrim(line, " \t");
	if (!trimmed_line)
		return (1);
	flag = parse_texture_or_color(line, trimmed_line, cube);
	free(trimmed_line);
	if (flag)
	{
		free_line(line, cube);
		error_exit();
	}
	return (0);
}

void	parse_map(char *line, t_cube *cube)
{
	int		map_size;
	char	**tmp;
	int		i;
	if (cube->map != NULL)
		map_size = array_len(cube->map);
	else
	{
		printf("initial map size\n");
		map_size = 0;
	}
	printf("line[%d]: %s\n", map_size, line);
	cube->max_y_size = map_size;
	tmp = ft_calloc(sizeof(char *), (map_size + 2));
	i = -1;
	while (++i < map_size)
		tmp[i] = cube->map[i];
	tmp[i] = ft_strtrim(line, "\n");
	free(cube->map);
	cube->map = tmp;
}
