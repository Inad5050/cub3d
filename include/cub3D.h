/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/22 18:56:41 by dangonz3         ###   ########.fr       */
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
# define PLAYER_WIDHT 1
# define PLAYER_HEIGHT 1
# define STEP_SIZE 4
# define FIELD_OF_VIEW 0.66 //para que el angulo de vision de la camara sea de aproximadamente 60 grados, lo habitual para un videojuego 3D
# define PI 3.14159265
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
# define GREEN 0x0000FF00
# define WHITE 0x00FFFFFF

//map_parts
# define FLOOR 'f'
# define WALL 'w'
# define CEILLING 'c'

//cardinal directions
# define EAST 0
# define NORTH 1
# define WEST 2
# define SOUTH 3

//-------------------------------------------------------
//sacado de la parte de parse, lo comentado no está en uso
//MAS ADELANTE ELIMINAR UNO DE LOS VALORES REPETIDOS DE CADA PAREJA

//bools
# define FALSE 0
# define TRUE 1

# define TILE_SIZE CELL_WIDHT
# define WINDOW_WIDTH WIN_WIDHT
# define WINDOW_HEIGHT WIN_HEIGHT
# define NUM_RAYS WINDOW_WIDTH

//-------------------------------------------------------

//float ocupa 4 bytes y tiene una capacidad de entre 6/7 decimales. double ocupa 8 y tiene una capacidad de hasta 15/16. Para este proyecto con float vale.

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

typedef struct s_ray
{
	//horientacion del rayo
	int		isRayFacingDown;
	int		isRayFacingUp;
	int		isRayFacingLeft;
	int		isRayFacingRight;

	//las coordenadas X e Y donde vamos a tocar la pared, las usamos para calcular la interseccion horizontal y luego la vertical
	float	xintercept;
	float	yintercept;
	
	//es la distancia que el rayo debe recorrer en cada eje empezando por el principio de una celda y hasta el final de la siguiente. Nos interesa la diferencia de longitud entre uno y otro. Ejem: Cuando intentamos encontrar el punto de corte horizontal sabemos que el vector en el eje Y es TILE_SIZE, si es así cuanto mide el vector en el eje X hasta el punto de corte horizontal? se calcula con la tangente (en este caso: adyacente (vctor X) = opuesto (ctor Y)/tan(angulo del rayo)). Uno de ellos sera siempre TILE_SIZE (la Y calculando la interseccion horizontal, la X calculando la interseccion vertical). 
	float	xstep;
	float	ystep;

	//variables del WHILE
	float	nextHorzTouchX; //la primera vez sera la distancia entre la posicion del jugador comparada con xintercept e yintercept. Una vez comience el bucle while el rayo estara sobre el eje X de una de las casillas y la distancia hasta el eje X de la siguiente casillas sera siempre la misma: xstep y ystep
	float	nextHorzTouchY;
	float	xToCheck; //altera nextHorzTouchX y nextHorzTouchY en funcion de la horientacion del rayo 
	float	yToCheck;
	
	//cuando el rayo choca contra la pared recabamos estos datos
	float	horizontalWallHitX;
	float	horizontalWallHitY;
	char	horizontalWallContent;
	int		foundHorizontalWallHit;

	float	verticalWallHitX;
	float	verticalWallHitY;
	char	verticalWallContent;
	int		foundVerticalWallHit;
	
	float	nextvertouchx;
	float	nextvertouchy;
	
} t_ray;

typedef struct s_cub
{
	void	*mlx; //puntero a la instancia de MLX
	void	*win_mlx_2D; //puntero a la ventana creada por MLX
	void	*win_mlx_3D;
	char	**map; //matriz con los caracteres del mapa

	float	player_fov; //ALGORITMO init_game. valor estatico

	int		map_axis_y; //cantidad de caracteres del mapa en el eje vertical
	int		map_axis_x; //cantidad de caracteres del mapa en el eje horizontal

	t_img	*ceiling;
	t_img	*floor;
	t_img	*wall_n;
	t_img	*wall_s;
	t_img	*wall_w;
	t_img	*wall_e;
	t_img	*player_img;
	
	float	p_y; //coordenadas del jugador sobre el eje vertical
	float	p_x; //coordenadas del jugador sobre el eje horizontal
	
	float	p_rotationangle; //ALGORITMO //angulo del jugador

	t_ray	*rays;
	
} t_cub;

//3D_init
int		init_3D(t_cub *c);

//3D_render
void	render_3Dmap(t_cub *c);
void	select_3Dmap(int y, int x, t_cub *c);
void	print_3Dmap(int y, int x, int color, t_cub *c);
int		modify_alpha(int color, int x, t_cub *c);

//exit
void	c_error(char *str, t_cub *c);
int		c_close(t_cub *c);
void	free_memory(t_cub *c);

//init_game
int		init_game(t_cub *c);
int		init_image(t_cub *c, t_img **c_img_ptr, char *route);
int		init_player_image(t_cub *c, t_img **c_img_ptr, char *route);
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

//ray_caster_utils
float	normalizeAngle(float angle);
int		mapHasWallAt(t_cub *c, float x, float y);

//ray_caster_horizontal
void	find_horizontal_hit(t_cub *c, t_ray	*r, float rayAngle, int stripid);
void	find_horizontal_hit_loop(t_cub *c, t_ray *r, float rayAngle, int stripid);

//ray_caster_vertical
void	find_vertical_hit(t_cub *c, t_ray	*r, float rayAngle, int stripid);
void	find_vertical_hit_loop(t_cub *c, t_ray *r, float rayAngle, int stripid);

//ray_caster
void	cast_all_rays(t_cub *c);
int		cast_ray_setup(t_cub *c, float rayAngle, int stripid);
void	reset_ray_struct(t_ray *r, float rayAngle);

#endif