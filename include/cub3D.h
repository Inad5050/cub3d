/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/15 13:58:19 by dangonz3         ###   ########.fr       */
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
# define FIELD_OF_VIEW 0.66 //para que el angulo de vision de la camara sea de aproximadamente 60 grados, lo habitual para un videojuego 3D
# define PI 3.1415926535
# define ANGLE_ROTATION_SIZE 5

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

//colors
# define BLUE 0x000000FF
# define PURPLE 0x00800080
# define WHITE 0x00FFFFFF

//map_parts
# define FLOOR 1
# define WALL 2
# define CEILLING 3

//cardinal directions
# define EAST 0
# define NORTH 1
# define WEST 2
# define SOUTH 3

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
	void	*win_mlx_2D; //puntero a la ventana creada por MLX
	void	*win_mlx_3D;
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
	double	p_angle; //angulo del jugador
	double	p_angle_y; //delta x del angulo del jugador
	double	p_angle_x;

	double	camera_x; //eje x del angulo de la camara actual. Son tangentes a los ejes del angulo del jugador [mirar init_player()], el valor de la tangente de un angulo de 60 grados es más o menos 0.66 (FOV, estático)
	double	camera_y;

	int		ray_index; //indice del rayo en la pantalla, iremos creando rayos verticales (sobre el eje x) hasta cubrir la anchura("0 x = %d\n", x);
	double	relative_ray_index; //indice relativo a la anchura de la camara (WIN_WIDHT) de los rayos que vamos a proyectar. Su valor va desde -1 a 1.
	double	ray_dx; //delta x del angulo del rayo. Dicho de otra forma: componente x del angulo del rayo.
	double	ray_dy;

	int		map_edge_x; //borde de la cuadricula más cercano a la posicion actual del jugador
	int		map_edge_y;
	double	delta_dist_x; //c->delta_dist_x y c->delta_dist_y son la distancia relativa (relativa a CELL_WIDHT y CELL_HEIGHT) que el rayo debera recorrer con su angulo actual (tanto en el eje x como en el y) para superar la distancia comprendida por el lado de uno de los rectangulos de la cuadricula del mapa 2D (osease CELL_WIDHT y CELL_HEIGHT para cada uno de sus relativos ejes)
	double	delta_dist_y;
	
	int		step_x; //indican en qué sentido debe avanzar el rayo. step_x: Si el rayo avanza hacia la derecha, será 1. Si avanza hacia la izquierda, será -1. Step_y: si el rayo avanza hacia arriba, será -1. Si avanza hacia abajo, será 1
	int		step_y; 
	double	side_dist_x; //son la distancia absoluta hasta el siguiente rectangulo si el jugador mantiene el rumbo actual. (c->p_x - c->map_edge_x) es la distancia más corta posible hasta el siguiente rectangulo del mapa (es perpendicular al eje al que queremos llegar). Esa distancia inicial se multiplica por c->delta_dist_x, para tener en cuenta que podemos no estar yendo en la dirección ideal
	double	side_dist_y;
	
	int		side; //c->side es un interruptor, inidica contra que eje del cuadrado va a chocar el rayo, si el x o el y
	
	double	wall_dist; //la ditancia a la pared mas cercana
	int		line_height; //la altura de la pared
	int		draw_start; //donde empezamos a dibujar la pared
	int		draw_end; //donde terminamos de dibujar la pared
	double	wall_height; //DUDA

	char	**map_3D; //matriz de cada pixel en pantalla

} t_cub;

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
void	draw_rays_3Dmap(int x, t_cub *c);

//3D_init
int		init_3D(t_cub *c);

//3D_render
void	render_3Dmap(t_cub *c);
void	select_3Dmap(int y, int x, t_cub *c);
void	print_3Dmap(int y, int x, int color, t_cub *c);

#endif
