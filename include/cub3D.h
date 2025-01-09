/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/09 20:18:51 by dangonz3         ###   ########.fr       */
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
# define CELL_WIDHT 64
# define CELL_HEIGHT 64
# define PLAYER_WIDHT 16
# define PLAYER_HEIGHT 16
# define STEP_SIZE 16
# define FIELD_OF_VIEW 0.66
# define PI 3.1415926535
# define ANGLE_ROTATION_SIZE 5

//cardinal directions
# define EAST 0
# define NORTH 1
# define WEST 2
# define SOUTH 3

//keybinds
# define KEY_ESC  		65307
# define KEY_W			119
# define KEY_S			115
# define KEY_A			97
# define KEY_D			100
# define KEY_LEFT  		65361
# define KEY_RIGHT 		65363

//events
# define ON_KEYDOWN		2
# define ON_DESTROY	   	17

//routes
# define ROUTE_CEILING "./textures/xpm/space/blue.xpm"
# define ROUTE_FlOOR "./textures/xpm/floor_62.xpm"
# define ROUTE_NORTH "./textures/xpm/grey_wall.xpm"
# define ROUTE_SHOUT "./textures/xpm/grey_wall.xpm"
# define ROUTE_WEST "./textures/xpm/grey_wall.xpm"
# define ROUTE_EAST "./textures/xpm/grey_wall.xpm"
# define ROUTE_PLAYER "./textures/xpm/player_small.xpm"

typedef struct s_image
{
	void	*img_ptr; 
	int		height;
	int		width;
	void	*addr; //puntero a la dirección de memoria inicial donde están almacenados los datos de los píxeles de la imagen.
	int		bpp; //(bits_per_pixel) el número de bits utilizados para representar cada píxel de la imagen.
	int		line_len; //el tamaño (en bytes) de cada fila de la imagen.
	int		endian; //el orden de los bytes (endianness) usado para representar los colores.
	char	*buffer;
} t_img;


typedef struct s_cub
{
	void	*mlx; //puntero a la instancia de MLX
	void	*win_mlx; //puntero a la ventana creada por MLX
	char	**map; //matriz con los caracteres del mapa

	int		map_axis_y; //cantidad de caracteres del mapa en el eje vertical
	int		map_axis_x; //cantidad de caracteres del mapa en el eje horizontal

	t_img	*ceiling;
	t_img	*floor;
	t_img	*wall_n;
	t_img	*wall_s;
	t_img	*wall_w;
	t_img	*wall_e;
	t_img	*player_img;

	double	p_y; //coordenadas del jugador sobre el eje vertical
	double	p_x; //coordenadas del jugador sobre el eje horizontal
	double	p_dy; //delta x
	double	p_dx; //delta y
	double	p_a; //angulo del jugador

	double	plane_x; //perpendicular de delta x
	double	plane_y; //perpendicular de delta y

	double	ray_camera; //posicion horizontal del rayo sobre el plano de la camara
	
	double	ray_dx;
	double	ray_dy;

	double	delta_dist_x; 
	double	delta_dist_y; 
	int		step_x; //indican en qué dirección debe avanzar el rayo a través de la cuadrícula. step_x: Si el rayo avanza hacia la derecha, será 1. Si avanza hacia la izquierda, será -1. 
	int		step_y; //step_y: Si el rayo avanza hacia arriba, será 1. Si avanza hacia abajo, será -1
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		side;
	double	wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_height;
	
	int		cardinal_direction;
}	
t_cub;

//exit
void	c_error(char *str, t_cub *c);
int		c_close(t_cub *c);
void	free_memory(t_cub *c);

//init_game
int		init_game(t_cub *c);
int		init_image(t_cub *c, t_img **c_img_ptr, char *route);
int		init_ply_image(t_cub *c, t_img **c_img_ptr, char *route);
void	*locate_player(t_cub *c);
void	init_player(int y, int x, t_cub *c);

//key_hooks
int		key_hooks(int keysym, t_cub *c);
int		is_in_wall(int y, int x, t_cub *c);
void	rotate_player(int right_dir, t_cub *c);

//map_read
void	map_read(char **argv, t_cub *c);
char	*sl_strjoin(char *s1, const char *s2);
void	get_map_axix_x(t_cub *c);

//map_render
void	map_render(t_cub *c);
void	map_select_element(int y, int x, t_cub *c);
void	map_print(int y, int x, t_img *c_img, t_cub *c);
void	player_print(double y, double x, t_img *c_img, t_cub *c);

//ray_caster
void	ray_direction(t_cub *c);
void	delta_distance(t_cub *c);
void	initial_distance(t_cub *c);
void	digital_differential_analysis(t_cub *c);
void	wall_distance(t_cub *c);

#endif
