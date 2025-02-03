/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_check_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:35:49 by otboumeh          #+#    #+#             */
/*   Updated: 2025/02/03 14:32:53 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3D.h"

/* verificating the format of the file if its end with .cub .*/
void	check_extension(char *argv1, t_cube *cube)
{
	int	i;

	i = ft_strlen(argv1);
	if (ft_strncmp(&argv1[i - 4], ".cub", 4) != 0)
	{
		printf("\nError\n Map file must have .cub extension. \n");
		exit(1);
	}

	cube++; //DANI: pongo esto para que me deje compilar
	
}
/* reading the file.cub and analizing every line by calling the function parse_line */ 
int	read_file(char *file, t_cube *cube)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Can't read the file\n"), 1);
	line = ft_get_next_line(fd);
	if (!line)
		return (ft_printf("File is empty\n"), 1);
	if (line[0] != '\n' && line[0] != '\0')
		parse_line(line, cube);
	free(line);
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n' && line[0] != '\0')
			parse_line(line, cube);
		free(line);
	}
	close(fd);

	return (0);
}
