/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_cube.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:24:06 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/13 21:09:17 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//mlx_init(int32_t width, int32_t height, const char* title, bool resize);

t_cube	*initiate_cube(char **argv)
{
	t_cube	*c;
	
	c = ft_calloc(1, sizeof(t_cube));
	if (!c)
		return (ft_printf("Couldn`t alloc t_cube c"), exit(EXIT_FAILURE), NULL);
	
	ft_printf("OLABEBE1\n");
	
	c->mlx = mlx_init(WIN_WIDHT, WIN_HEIGHT, "SUPER CUB3D", true);
	if (!c->mlx)
		c_error("Error in mlx_init", c);
	
	ft_printf("OLABEBE2\n");

/* 	read_map_PROVISIONAL(argv, c);  //copia + pega so_long no funciona con cube
	
	c->time_initial = mlx_get_time();

	get_png_route(c); */

	//..

	return (c);
}

void	read_map_PROVISIONAL(char **argv, t_cube *c) //copia + pega so_long no funciona con cube
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

void	get_png_route(t_cube *c)
{
	c->png_floor = ft_strdup("./textures/png/backrooms/default/floor.png");
	if (!c->png_floor)
		c_error("Couldn't alloc in initiate_cube", c);
	c->png_wall = ft_strdup("./textures/png/backrooms/default/wall.png");
	if (!c->png_wall)
		c_error("Couldn't alloc in initiate_cube", c);

	//...
	
}