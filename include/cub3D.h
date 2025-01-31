/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/31 14:53:33 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../mlx/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <math.h>
# include <limits.h>
# include <stdint.h>

//sizes
# define WIN_WIDHT 2000
# define WIN_HEIGHT 1000
# define CELL_SIZE 128
# define PLAYER_SIZE 10
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

//colors
# define RED 0xFFFF0000 //los primeros dos hexadecimales FF o 00
# define BLUE 0x000000FF
# define GREEN 0x0000FF00
# define WHITE 0x00FFFFFF
# define PURPLE 0x800080FF
# define ORANGE 0xFFA500FF

//canvas_colors
# define CEILING_COLOR BLUE
# define FlOOR_COLOR WHITE
 
//routes
# define ROUTE_NORTH "./textures/NO.png"
# define ROUTE_SHOUT "./textures/SO.png"
# define ROUTE_WEST "./textures/WE.png"
# define ROUTE_EAST "./textures/EA.png"

//map_parts
# define FLOOR 'f'
# define WALL 'w'
# define CEILLING 'c'

//cardinal directions
# define EAST 0
# define NORTH 1
# define WEST 2
# define SOUTH 3

//bools
# define FALSE 0
# define TRUE 1

//ray_caster
# define TILE_SIZE WIN_WIDHT
# define WINDOW_WIDTH WIN_WIDHT
# define WINDOW_HEIGHT WIN_HEIGHT
# define NUM_RAYS WINDOW_WIDTH

//codium_library
# define BPP sizeof(int32_t) //Only support RGBA
# define LCT_RGBA 6	//RGB with alpha: 8,16 bit

//others
# define FRAMES 30

typedef struct s_render_params
{
	float				perp_distance;
	float				distance_proj_plane;
	float				wall_strip_height;
	int					wall_top_pixel;
	int					wall_bottom_pixel;
	unsigned int		wall_color;
}	t_render_params;

typedef struct s_texture
{
	int					width;
	int					height;
	unsigned int		**pixels;
}	t_texture;

//CODIUM

/* typedef struct mlx_texture //estructura de la lebreria de CODAM
{
	uint32_t	width; //The width of the texture.
	uint32_t	height; //The height of the texture.
	uint8_t		bytes_per_pixel; //The amount of bytes in a pixel, always 4.
	uint8_t*	pixels; //The literal pixel data.
}	mlx_texture_t; */

//--------------------

typedef struct s_ray
{
	float	rayangle; //el angulo del rayo, su valor depende de la horientacion de la vision del jugador. Lo incrementamos con cada rayo sucesivo que lanzamos
	int		ray_index;
	
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
	float	nextVerticalTouchX; //la primera vez sera la distancia entre la posicion del jugador comparada con xintercept e yintercept. Una vez comience el bucle while el rayo estara sobre el eje X de una de las casillas y la distancia hasta el eje X de la siguiente casillas sera siempre la misma: xstep y ystep
	float	nextVerticalTouchY;
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

	//comprobamos que distancia es más corta	
	float	horizontalHitDistance;
	float	verticalHitDistance;
	
	//elegimos que datos vamos a usar (los del hit horizontal o vertical) y los almacenamos
	float	distance;
	float	wallHitX;
	float	wallHitY;
	float	wallHitContent;
	float	wasHitVertical;

	//MEDIUM BLOG
	float	distance_medium; //parte del codigo del blog medium para renderizar los rayos
	int		flag; //identifica la horientacion de la pared a la que estamos casteando

	//render
	float	perp_distance;
	float	distance_proj_plane;
	float	wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	unsigned int	wall_color;
} t_ray;

typedef struct s_cub
{
	void		*mlx; //puntero a la instancia de MLX
	mlx_image_t	*win_mlx3D;
	char		**map; //matriz con los caracteres del mapa
	int			player_direction;
	int			map_axis_y; //cantidad de caracteres del mapa en el eje vertical
	int			map_axis_x; //cantidad de caracteres del mapa en el eje horizontal
	
	unsigned int	ceiling;
	unsigned int	floor;
	t_texture		*wall_n;
	t_texture		*wall_s;
	t_texture		*wall_w;
	t_texture		*wall_e;
	
	float		p_fov; //init_game. valor estatico. Lo usamos durante el casteo para determinar el angulo de los rayos
	float		p_turnspeed; //velocidad a la que rota el jugador cada vez que pulsamos MLX_KEY_LEFT y MLX_KEY_RIGHT
	float		p_walkspeed; //velocidad de movimiento del jugador
	
	float		p_rotationangle; //angulo del jugador
	float		p_y; //coordenadas del jugador sobre el eje vertical
	float		p_x; //coordenadas del jugador sobre el eje horizontal
	
	int			p_turndirection;
	int			p_walkdirection;
	int			p_strafedirection;

	t_ray		*rays; //estructuras correpondientes a cada rayo

	unsigned int	strip[WINDOW_HEIGHT];
	unsigned int	timelastframe;
} t_cub;

//3D_init
int		init_3D(t_cub *c);

/* //codium_render
mlx_texture_t* mlx_load_png(const char* path, t_cub *c);
unsigned lodepng_decode32_file(unsigned char** out, unsigned* w,
 unsigned* h, const char* filename); */

//exit
void		c_error(char *str, t_cub *c);
void		c_close(t_cub *c);
void		free_memory(t_cub *c);

//init_game
int			init_game(t_cub *c);
int			init_texture_struct(t_cub *c, t_texture **strc, char *route);
int			init_texture_struct_aux(t_cub *c, t_texture *texture, mlx_texture_t	*png);
uint32_t	get_color(uint8_t *ptr); 

//init_map
void		init_map(char **argv, t_cub *c);
char		*sl_strjoin(char *s1, const char *s2);
void		get_map_axix_x(t_cub *c);

//init_player
void		init_player(t_cub *c);
int			locate_player(t_cub *c);
void		init_player_inmap(int y, int x, t_cub *c);

//init_textures
int			load_sprite(t_texture *text, int x, int y);

//handle_player_input
int			handle_player_input(void *param);
int			update_player_position(t_cub *c);
int			check_wall_collision(t_cub *c, float x, float y);
int			rotate_player(t_cub *c);

//main
void		game_loop(void *param);

//ray_caster_hit_wall
void		find_horizontal_hit(t_cub *c, t_ray *r, float rayAngle);
void		find_horizontal_hit_loop(t_cub *c, t_ray *r);
void		find_vertical_hit(t_cub *c, t_ray *r, float rayAngle);
void		find_vertical_hit_loop(t_cub *c, t_ray *r);

//ray_caster_utils
float		normalize_angle(float angle);
int			mapHasWallAt(t_cub *c, float x, float y);
float		distanceBetweenPoints(float x1, float y1, float x2, float y2);

//ray_caster
void		ray_caster(t_cub *c);
void		cast_ray(t_cub *c, t_ray *r, int ray_index, float rayAngle);
void		init_ray_struct(t_ray *r, int ray_index, float rayAngle);
void		choose_ray_hit(t_cub *c, t_ray *r);

//ray_render
void		ray_render(t_cub *c);
int			init_data_render(t_cub *c, t_ray *r);
void		render(t_cub *c, t_ray *r);
void		render_strip(t_cub *c, int x);
void		get_strip(t_cub *c, t_ray *r, t_texture *text, int x);

#endif