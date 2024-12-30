/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/12/30 21:00:59 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdbool.h>
# include <math.h>

# define WIN_WIDHT 1300
# define WIN_HEIGHT 800
# define IMG_WIDHT 64
# define IMG_HEIGHT 64
# define STEP_SIZE 8

# define ROUTE_CEILING "./textures/xpm/space/blue.xpm"
# define ROUTE_FlOOR "./textures/xpm/floor.xpm"
# define ROUTE_NORTH "./textures/xpm/wolfestein/blue_wall.xpm"
# define ROUTE_SHOUT "./textures/xpm/wolfestein/brick_wall.xpm"
# define ROUTE_WEST "./textures/xpm/wolfestein/grey_wall.xpm"
# define ROUTE_EAST "./textures/xpm/wolfestein/steel_wall.xpm"

// ---------------------- MLX ----------------------

typedef struct s_player
{
	/* double			player_angle; */
	double	p_y;
	double	p_x;
	int		p_y_floor;
	int		p_x_floor;
	int		p_y_ceil;
	int		p_x_ceil;
/* 	int		w_flag;
	int		s_flag;
	int		a_flag;
	int		d_flag;
	int		r_flag;
	int		l_flag;
	int		colition;
	float	col_x;
	float	col_y; */
} t_plyr;

typedef struct s_image
{
	void	*img_ptr;
	int		height;
	int		width;
	void	*addr; //puntero a la dirección de memoria inicial donde están almacenados los datos de los píxeles de la imagen.
	int		bpp; //(bits_per_pixel) el número de bits utilizados para representar cada píxel de la imagen.
	int		line_len; //el tamaño (en bytes) de cada fila de la imagen.
	int		endian; //el orden de los bytes (endianness) usado para representar los colores.
} t_img;

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	char	**map;
/* 	char	**map_cop;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*t_f;
	char	*t_c;
	int		rgb_up[3];
	int		rgb_down[3]; */
	int		map_axis_y;
	int		map_axis_x;
	int		map_bool;

	t_plyr	*p;

	t_img	*ceiling;
	t_img	*floor;
	t_img	*wall_n;
	t_img	*wall_s;
	t_img	*wall_w;
	t_img	*wall_e;
}	t_cub;

// ---------------------- MLX ----------------------

//errors
void	c_error(char *str, t_cub *c);
void	free_memory(t_cub *c);

//init_game
int		init_game(t_cub *c);
int		init_image(t_cub *c, t_img **c_img_ptr, char *route);

//loops
void	loops(t_cub *c);
void	key_hooks(void *c_void);

//map_read
void	map_read(char **argv, t_cub *c);
char	*sl_strjoin(char *s1, const char *s2);

//map_render
void	map_render(t_cub *c);
void	map_select_element(int y, int x, t_cub *c);
void	map_print(int y, int x, t_img *c_img, t_cub *c);

//player_move
void	player_move(t_cub *c);

#endif
