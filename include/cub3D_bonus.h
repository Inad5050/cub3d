/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/07 20:40:38 by dangonz3         ###   ########.fr       */
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
# define PLAYER_SIZE 10
# define PI 3.14159265
# define ANGLE_ROTATION_SIZE 5
# define FRAMES 30 
# define TILE_SIZE 1000
# define NUM_RAYS WIN_WIDHT

//bools
# define FALSE 0
# define TRUE 1

//minimap colors
# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF

//door
# define OPEN_TIME 60
# define OPEN_DISTANCE TILE_SIZE * 2
# define DOOR_ROUTE "./texture/doom_door.png"

//sprite
# define SPRITE_ROUTE "./texture/cocodemon.png"
# define WHITE_DECIMAL 4294967295

typedef struct s_player_position
{
	int				x;
	int				y;
	int				pos_x;
	int				pos_y;
	char			orientation;
}			t_player_position;

typedef struct s_cube
{
    char        	**map;               // The parsed map
    int         	player_x;            // Player's X position
    int         	player_y;            // Player's Y position
    char        	*north_texture;      // North texture path
    char        	*south_texture;      // South texture path
    char        	*west_texture;       // West texture path
    char        	*east_texture;       // East texture path
    int         	floor_color[3];      // Floor color (RGB)
    int         	ceiling_color[3];    // Ceiling color (RGB)
    int         	max_y_size;          // Max Y size of the map
    int         	max_x_size;          // Max X size of the map
    char       		*raw_map;            // Temporary raw map
} t_cube;

typedef struct s_door
{
	int				x_door;
	int				y_door;
	int				is_closed;
	int				opening;
}	t_door;


typedef struct s_texture //buffer para renderizar PNGs
{
	int				width;
	int				height;
	unsigned int	**pixels;
}	t_texture;

typedef struct s_ray
{
	float			rayangle; //el angulo del rayo, su valor depende de la horientacion de la vision del jugador. Lo incrementamos con cada rayo sucesivo que lanzamos
	int				ray_index;
	
	int				isRayFacingDown; //horientacion del rayo
	int				isRayFacingUp;
	int				isRayFacingLeft;
	int				isRayFacingRight;

	float			xintercept; //las coordenadas X e Y donde vamos a tocar la pared, las usamos para calcular la interseccion horizontal y luego la vertical
	float			yintercept;
	
	float			xstep; //es la distancia que el rayo debe recorrer en cada eje empezando por el principio de una celda y hasta el final de la siguiente. Nos interesa la diferencia de longitud entre uno y otro. Ejem: Cuando intentamos encontrar el punto de corte horizontal sabemos que el vector en el eje Y es TILE_SIZE, si es así cuanto mide el vector en el eje X hasta el punto de corte horizontal? se calcula con la tangente (en este caso: adyacente (vctor X) = opuesto (ctor Y)/tan(angulo del rayo)). Uno de ellos sera siempre TILE_SIZE (la Y calculando la interseccion horizontal, la X calculando la interseccion vertical).
	float			ystep;

	//variables del WHILE
	float			next_horz_touch_x; //la primera vez sera la distancia entre la posicion del jugador comparada con xintercept e yintercept. Una vez comience el bucle while el rayo estara sobre el eje X de una de las casillas y la distancia hasta el eje X de la siguiente casillas sera siempre la misma: xstep y ystep
	float			next_horz_touch_y;
	float			next_vertical_touch_x; //la primera vez sera la distancia entre la posicion del jugador comparada con xintercept e yintercept. Una vez comience el bucle while el rayo estara sobre el eje X de una de las casillas y la distancia hasta el eje X de la siguiente casillas sera siempre la misma: xstep y ystep
	float			next_vertical_touch_y;
	float			x_to_check; //altera next_horz_touch_x y next_horz_touch_y en funcion de la horientacion del rayo 
	float			y_to_check;
	
	float			horizontal_wall_hit_x;	//cuando el rayo choca contra la pared recabamos estos datos
	float			horizontal_wall_hit_y;
	char			horizontal_wall_content;
	int				found_horizontal_wall_hit;
	float			vertical_wall_hit_x;
	float			vertical_wall_hit_y;
	char			vertical_wall_content;
	int				found_vertical_wall_hit;

	float			horizontal_hit_distance;	//comprobamos que distancia es más corta	
	float			vertical_hit_distance;

	float			distance;	//elegimos que datos vamos a usar los del hit horizontal o vertical y los almacenamos
	float			wall_hit_x;
	float			wall_hit_y;
	float			was_hit_vertical;
	
	float			perp_distance;	//renderizado
	float			distance_proj_plane;
	float			wall_strip_height;
	int				wall_top_pixel;
	int				wall_bottom_pixel;
	unsigned int	wall_color;

	int				is_sprite;
	float			horizontal_sprite_hit_x;
	float			horizontal_sprite_hit_y;
	float			vertical_sprite_hit_x;
	float			vertical_sprite_hit_y;
	float			sprite_horizontal_hit_distance;
	float			sprite_vertical_hit_distance;
	float			sprite_hit_x;
	float			sprite_hit_y;
	float			sprite_distance;
	int				sprite_was_hit_vertical;

	float			sprite_perp_distance;
	float			sprite_distance_proj_plane;
	float			sprite_strip_height;
	int				sprite_top_pixel;
	int				sprite_bottom_pixel;

	int				im_door;
	int				im_door_number;
} t_ray;

typedef struct s_cub
{
	void			*mlx; //puntero a la instancia de MLX
	mlx_image_t		*win_mlx3D;

	t_cube			*parse_struct; //puntero al parseo

	char			**map; //matriz con los caracteres del mapa
	int				player_direction;
	int				map_max_y; //cantidad de caracteres del mapa en el eje vertical
	int				map_max_x; //cantidad de caracteres del mapa en el eje horizontal
	
	unsigned int	ceiling; //colores && texturas
	unsigned int	floor;
	t_texture		*wall_n;
	t_texture		*wall_s;
	t_texture		*wall_w;
	t_texture		*wall_e;
	t_texture		*door_t;

	t_texture		*sprite_texture;
	
	float			p_fov; //init_game. valor estatico. Lo usamos durante el casteo para determinar el angulo de los rayos
	float			p_turnspeed; //velocidad a la que rota el jugador cada vez que pulsamos MLX_KEY_LEFT y MLX_KEY_RIGHT
	float			p_walkspeed; //velocidad de movimiento del jugador
	float			p_turnspeed_original;
	
	float			p_rotationangle; //angulo del jugador
	float			p_y; //coordenadas del jugador sobre el eje vertical
	float			p_x; //coordenadas del jugador sobre el eje horizontal
	
	int				p_walkdirection; //flags de movimiento del jugador
	int				p_strafedirection;
	int				p_turndirection; 

	t_ray			*rays; //estructuras correpondientes a cada rayo

	unsigned int	strip[WIN_HEIGHT]; //buffer para proyectar las texturas
	
	unsigned int	timelastframe; //controla las frames/s del juego

	float			minimap_start_y;
	float			minimap_start_x;
	float			minimap_area_y;
	float			minimap_area_x;
	float			minimap_tile_size;
	float			minimap_player_size;

	unsigned int	sprite_strip[WIN_HEIGHT];

	t_door 			*doors;
	int 			door_number;
} t_cub;

//doors
void		init_doors(t_cub *c);
void		locate_doors(t_cub *c);
void		open_doors(t_cub *c);
void		detect_doors(t_cub *c, t_ray *r);
void		update_doors(t_cub *c);

//exit
void		c_error(char *str, t_cub *c);
void		c_close(t_cub *c);
void		free_memory(t_cub *c);
void 		free_t_texture(t_texture *t);

//init_game
int			init_game(t_cub *c);
int			load_texture(t_cub *c, t_texture **strc, char *route);
int			load_texture_aux(t_cub *c, t_texture *texture, mlx_texture_t *png);
void		get_map_max_x(t_cub *c);

//init_player
void		init_player(t_cub *c);
int			locate_player(t_cub *c);
void		set_player_position(int y, int x, t_cub *c);

//main
void		game_loop(void *param);

//minimap
void		minimap_render(t_cub *c);
void		minimap_print(int x_map, int y_map, uint32_t element, t_cub *c);
void		minimap_print_player(t_cub *c);
/* int			minimap_next_wall(float x, float y, t_cub *c); */
void		init_minimap(t_cub *c);

//p_check_map.c
void		check_extension(char *argv1);
int			read_file(char *file, t_cube *cube);

//p_freedom.c
void		free_line(char *line, t_cube *cube);
void		free_content(t_cube *cube);
void		array_free(char **array);

//p_map_parsing
int			validate_map(t_cube *cube, t_player_position *player_position);

//p_parser.c
void		check_arg_number(int argc);
int			verification_start(t_cube *cube,\
			t_player_position *player_position, char **argv);
int			parser(int argc, char **argv);
void 		reach_last_character(const char *file_path);

//p_parsing.c
int			parse_line(char *line, t_cube *cube);
char		*line_verification(char *line);
int			parse_colors(char *line, int color[3]);
void		parse_map(char *line, t_cube *cube);

//p_util_map.c
void		delete_tab(char ***map, int i);
int			last_verification(t_cube *cube, t_player_position *player_position);
int			validate_file(t_cube *cube);

//p_utils.c
int			space_verification(char c);
int			array_len(char **array);
void 		error_exit();
int			is_number(const char *str);
void		set_initial_position(t_player_position *player_position, int x, int y,
			char orientation);

//process_player_input
void		process_player_input(void *param);
void		mouse_hook(t_cub *c);
void		update_player_position(t_cub *c);
int			check_wall_collision(t_cub *c, float x, float y);

//ray_caster_scan_hits
void		find_horizontal_hit(t_cub *c, t_ray *r, float rayAngle);
void		find_horizontal_hit_loop(t_cub *c, t_ray *r);
void		find_vertical_hit(t_cub *c, t_ray *r, float rayAngle);
void		find_vertical_hit_loop(t_cub *c, t_ray *r);
int			has_wall_at(t_cub *c, float x, float y);

//ray_caster
void		ray_caster(t_cub *c);
void		cast_ray(t_cub *c, t_ray *r, int ray_index, float rayAngle);
void		init_ray_struct(t_ray *r, int ray_index, float rayAngle);
void		select_ray_hit(t_cub *c, t_ray *r);

//ray_render
void		ray_render(t_cub *c);
int			init_data_render(t_cub *c, t_ray *r);
void		render(t_cub *c, t_ray *r);
void		calculate_wall_strip(t_cub *c, t_ray *r, t_texture *text, int x);
void		draw_wall_strip(t_cub *c, int x);

//sprite_render
void		choose_sprite_hit(t_cub *c, t_ray *r);
void		sprite_render(t_cub *c);
void		sprite_render_aux(t_cub *c, t_ray *r);
void		calculate_sprite_strip(t_cub *c, t_ray *r, t_texture *t, int x);
void		draw_sprite_strip(t_cub *c, t_ray *r, int x);

//utils
float		normalize_angle(float angle);
uint32_t	get_color(uint8_t *ptr);
uint32_t	get_color_alt(int *ptr);
float		distance_between_points(float x1, float y1, float x2, float y2);

#endif