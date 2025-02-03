/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:03:26 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/03 16:54:38 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* void	init_map(char **argv, t_cub *c) //lee el mapa
{
	char	*map_temp; //almacena los valores del mapa pre split()
	char	*line_temp; //buffer de get_next_line
	int		map_fd; //necesario para usar open()

	map_fd = open(argv[1], O_RDONLY);
	if (map_fd == -1)
		c_error("Can't open Map!", c);
	map_temp = ft_strdup("");
	if (!map_temp)
		c_error("Couldn't alloc in read_map_PROVISIONAL", c);
	while (1)
	{
		line_temp = ft_get_next_line(map_fd);
		if (!line_temp)
			break ;
		map_temp = sl_strjoin(map_temp, line_temp);
		free(line_temp);
		c->map_max_y++;
	}
	close(map_fd);
	c->map = ft_split(map_temp, '\n');
	free(map_temp);
	c->map_max_y--; //necesario?
	c->map_max_y *= TILE_SIZE;
	get_map_max_x(c);
}

char	*sl_strjoin(char *s1, const char *s2) // sl_strjoin personalizado del so_long
{
	int		i;
	int		len_s1;
	int		len_s2;
	char	*result;

	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		result[len_s1 + i] = s2[i];
		i++;
	}
	result[len_s1 + i] = '\0';
	free(s1);
	return (result);
} */
