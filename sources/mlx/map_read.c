/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:03:26 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/28 17:34:01 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	map_read(char **argv, t_cub *c)
{
	char	*map_temp;
	char	*line_temp;
	int		map_fd;

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
		c->map_axis_y++;
	}
	close(map_fd);
	c->map = ft_split(map_temp, '\n');
	c->map_bool = 1;
	free(map_temp);
}

char	*sl_strjoin(char *s1, const char *s2) //copia + pega so_long
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
}
