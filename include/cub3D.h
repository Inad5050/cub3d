/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/27 19:31:35 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../mlx/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <math.h>

# define IMG_WIDHT 64
# define IMG_HEIGHT 64

typedef struct s_cube
{
	mlx_t			*mlx;

	int				map_axis_y;
	int				map_axis_x;
	char			**map;
	int				map_bool;

	char			*png_floor;
	mlx_texture_t	*texture_floor;
	mlx_image_t		*img_floor;
	
	char			*png_wall;
	mlx_texture_t	*texture_wall;	
	mlx_image_t		*img_wall;

	char			*png_player;
	mlx_texture_t	*texture_player;	
	mlx_image_t		*img_player;

} t_cube;

//errors
void	free_memory(t_cube *c);
void	free_img(t_cube *c);

//free_memory
void	c_error(char *str, t_cube *c);
void	c_error_img(char *str, t_cube *c);

//image_load
void	image_load(t_cube *c);

//initiate_mlx
void	initiate_mlx(t_cube *c);
void	map_axis_x(t_cube *c);

//loops
void	loops(t_cube *c);
void	key_hooks(void *c_void);

//map_read
void	map_read(char **argv, t_cube *c);
char	*sl_strjoin(char *s1, const char *s2);

//map_render
void	map_render(t_cube *c);
void	map_identify(int i, int x, t_cube *c);

//player_movement
void	player_movement(t_cube *c);

#endif
