/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/07 19:25:04 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdbool.h>
# include <math.h>

//sizes
# define WIN_WIDHT 1300
# define WIN_HEIGHT 800
# define IMG_WIDHT 64
# define IMG_HEIGHT 64
# define STEP_SIZE 32

//keybinds
# define KEY_W			119
# define KEY_S			115
# define KEY_A			97
# define KEY_D			100
# define KEY_UP  		65362
# define KEY_DOWN  		65364
# define KEY_LEFT  		65361
# define KEY_RIGHT 		65363
# define KEY_ESC  		65307

//events
# define ON_KEYDOWN		2
# define ON_DESTROY	   	17
# define ON_EXPOSE  	12

//routes
# define ROUTE_CEILING "./textures/xpm/space/blue.xpm"
# define ROUTE_FlOOR "./textures/xpm/backrooms/default/floor.xpm"
# define ROUTE_NORTH "./textures/xpm/grey_wall.xpm"
# define ROUTE_SHOUT "./textures/xpm/grey_wall.xpm"
# define ROUTE_WEST "./textures/xpm/grey_wall.xpm"
# define ROUTE_EAST "./textures/xpm/grey_wall.xpm"
# define ROUTE_PLAYER "./textures/xpm/player.xpm"

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
} t_player;

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
	void	*win_mlx;
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

	t_player	*p;

	t_img	*ceiling;
	t_img	*floor;
	t_img	*wall_n;
	t_img	*wall_s;
	t_img	*wall_w;
	t_img	*wall_e;
	t_img	*player_img;
}	t_cub;

// ---------------------- MLX ----------------------

//exit
void	c_error(char *str, t_cub *c);
int		c_close(t_cub *c);
void	free_memory(t_cub *c);

//init_game
int		init_game(t_cub *c);
int		init_image(t_cub *c, t_img **c_img_ptr, char *route);
int		init_player_image(t_cub *c, t_img **c_img_ptr, char *route);

//key_hooks
int		key_hooks(int keysym, t_cub *c);
int		is_in_wall(int y, int x, t_cub *c);

//map_read
void	map_read(char **argv, t_cub *c);
char	*sl_strjoin(char *s1, const char *s2);
void	get_map_axix_x(t_cub *c);

//map_render
void	map_render(t_cub *c);
void	map_select_element(int y, int x, t_cub *c);
void	map_print(int y, int x, t_img *c_img, t_cub *c);
void	player_print(double y, double x, t_img *c_img, t_cub *c);
void	locate_player(int y, int x, t_cub *c);

#endif
