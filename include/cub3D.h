/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/12/26 20:10:43 by dangonz3         ###   ########.fr       */
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
# define STEP_SIZE 8

// ---------------------- MLX ----------------------

typedef struct s_cub
{
	mlx_t			*mlx;

	int				map_axis_y;
	int				map_axis_x;
	char			**map;
	int				map_bool;

	double			p_y;
	double			p_x;
	int				p_y_floor;
	int				p_x_floor;
	int				p_y_ceil;
	int				p_x_ceil;

	char			*png_floor;
	mlx_texture_t	*texture_floor;
	mlx_image_t		*img_floor;
	
	char			*png_wall;
	mlx_texture_t	*texture_wall;	
	mlx_image_t		*img_wall;

	char			*png_player;
	mlx_texture_t	*texture_player;	
	mlx_image_t		*img_player;

} t_cub;

// ---------------------- PARSER ----------------------

typedef struct s_player_position
{
	int		x;
	int		y;
	int		pos_x;
	int		pos_y;
	char	orientation;

}			t_player_position;

typedef struct s_cube
{
	// mlx_t			*mlx;
	char		**map;
	int				player_x;
	int				player_y;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_color[3];
	int			ceiling_color[3];
	int 		max_y;
	int 		max_x;
	// double			time_initial;

	// int				map_axis_y; //copia + pega so_long no funciona con cube
	// char				**map; //copia + pega so_long no funciona con cube
	// int				map_bool; //copia + pega so_long no funciona con cube

	// char				*png_floor;
	// mlx_texture_t	*texture_floor;
	// mlx_image_t		*img_floor;
	
	// char			*png_wall;
	// mlx_texture_t	*texture_wall;	
	// mlx_image_t		*img_wall;

} t_cube;

// ---------------------- MLX ----------------------

//errors
void	free_memory(t_cub *c);
void	free_img(t_cub *c);

//free_memory
void	c_error(char *str, t_cub *c);
void	c_error_img(char *str, t_cub *c);

//image_load
void	image_load(t_cub *c);

//initiate_mlx
void	initiate_mlx(t_cub *c);
void	map_axis_x(t_cub *c);

//loops
void	loops(t_cub *c);
void	key_hooks(void *c_void);

//map_read
void	map_read(char **argv, t_cub *c);
char	*sl_strjoin(char *s1, const char *s2);

//map_render
void	map_render(t_cub *c);
void	map_identify(int i, int x, t_cub *c);

//player_move
void	player_move(t_cub *c);
void	move(t_cub *c, int move_x, int move_y);

// ---------------------- PARSER ----------------------

//parsing.c
int		parse_line(char *line, t_cube *cube);
char	*line_verification(char *line);
int		parse_colors(char *line, int color[3]);
void	parse_map(char *line, t_cube *cube);

//check_map.c
void	check_extension(char *argv1, t_cube *cube);
int		read_file(char *file, t_cube *cube);

//freedom.c
void	free_line(char *line, t_cube *cube);
void	free_content(t_cube *cube);
void	array_free(char **array);

//main.c
void	check_arg_number(int argc);
int		verification_start(t_cube *cube,\
			t_player_position *player_position, char **argv);
int		parser(int argc, char **argv);

//util_map.c
void	delete_tab(char ***map, int i);
int		last_verification(t_cube *cube, t_player_position *player_position);
int		validate_file(t_cube *cube);

//utils.c
int		space_verification(char c);
int		array_len(char **array);
void 	error_exit();
int		is_number(const char *str);
void	set_initial_position(t_player_position *player_position, int x, int y,
		char orientation);
//print
char	*ft_sprintf(char const *container, ...);

//map_parsing
int	validate_map(t_cube *cube, t_player_position *player_position);

#endif
