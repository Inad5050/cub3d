/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/13 19:16:23 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../mlx/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <math.h>

# define WIN_WIDHT 512
# define WIN_HEIGHT 512
# define IMG_WIDHT 128
# define IMG_HEIGHT 128

typedef struct s_cube
{
	mlx_t			*mlx;

	int				player_x;
	int				player_y;
	
	double			time_initial;

	int				map_axis_y; //copia + pega so_long no funciona con cube
	char			**map_all; //copia + pega so_long no funciona con cube
	int				map_bool; //copia + pega so_long no funciona con cube

	char		*png_floor;
	mlx_texture_t	*texture_floor;
	mlx_image_t		*img_floor;
	
	char		*png_wall;
	mlx_texture_t	*texture_wall;	
	mlx_image_t		*img_wall;

} t_cube;

//errors
void	free_memory(t_cube *c);
void	free_img(t_cube *c);

//free_memory
void	c_error(char *str, t_cube *c);
void	c_error_img(char *str, t_cube *c);

//images
void	image_load(t_cube *c);
void	map_render(t_cube *c);
void	map_identify(int i, int x, t_cube *c);

//initiate_cube
t_cube	*initiate_cube(char **argv);
void	read_map_PROVISIONAL(char **argv, t_cube *c); //copia + pega so_long no funciona con cube
char	*sl_strjoin(char *s1, const char *s2); //copia + pega so_long
void	get_png(t_cube *c);

//loops
void	loops(t_cube *c);
void	key_hooks(t_cube *c);

#endif
