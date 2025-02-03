/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/03 17:37:07 by dangonz3         ###   ########.fr       */
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
# define TILE_SIZE WIN_WIDHT
# define NUM_RAYS WIN_WIDHT

//cardinal directions
# define EAST 0
# define NORTH 1
# define WEST 2
# define SOUTH 3

//bools
# define FALSE 0
# define TRUE 1

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
    char        **map;               // The parsed map
    int         player_x;            // Player's X position
    int         player_y;            // Player's Y position
    char        *north_texture;      // North texture path
    char        *south_texture;      // South texture path
    char        *west_texture;       // West texture path
    char        *east_texture;       // East texture path
    int         floor_color[3];      // Floor color (RGB)
    int         ceiling_color[3];    // Ceiling color (RGB)
    int         max_y_size;          // Max Y size of the map
    int         max_x_size;          // Max X size of the map
    char        *raw_map;            // Temporary raw map
} t_cube;

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
	float			nextHorzTouchX; //la primera vez sera la distancia entre la posicion del jugador comparada con xintercept e yintercept. Una vez comience el bucle while el rayo estara sobre el eje X de una de las casillas y la distancia hasta el eje X de la siguiente casillas sera siempre la misma: xstep y ystep
	float			nextHorzTouchY;
	float			nextVerticalTouchX; //la primera vez sera la distancia entre la posicion del jugador comparada con xintercept e yintercept. Una vez comience el bucle while el rayo estara sobre el eje X de una de las casillas y la distancia hasta el eje X de la siguiente casillas sera siempre la misma: xstep y ystep
	float			nextVerticalTouchY;
	float			xToCheck; //altera nextHorzTouchX y nextHorzTouchY en funcion de la horientacion del rayo 
	float			yToCheck;
	
	float			horizontalWallHitX;	//cuando el rayo choca contra la pared recabamos estos datos
	float			horizontalWallHitY;
	char			horizontalWallContent;
	int				foundHorizontalWallHit;
	float			verticalWallHitX;
	float			verticalWallHitY;
	char			verticalWallContent;
	int				foundVerticalWallHit;

	float			horizontalHitDistance;	//comprobamos que distancia es más corta	
	float			verticalHitDistance;

	float			distance;	//elegimos que datos vamos a usar los del hit horizontal o vertical y los almacenamos
	float			wallHitX;
	float			wallHitY;
	float			wallHitContent;
	float			wasHitVertical;
	
	float			perp_distance;	//render
	float			distance_proj_plane;
	float			wall_strip_height;
	int				wall_top_pixel;
	int				wall_bottom_pixel;
	unsigned int	wall_color;
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
	
	float			p_fov; //init_game. valor estatico. Lo usamos durante el casteo para determinar el angulo de los rayos
	float			p_turnspeed; //velocidad a la que rota el jugador cada vez que pulsamos MLX_KEY_LEFT y MLX_KEY_RIGHT
	float			p_walkspeed; //velocidad de movimiento del jugador
	
	float			p_rotationangle; //angulo del jugador
	float			p_y; //coordenadas del jugador sobre el eje vertical
	float			p_x; //coordenadas del jugador sobre el eje horizontal
	
	int				p_walkdirection; //flags de movimiento del jugador
	int				p_strafedirection;
	int				p_turndirection; 

	t_ray			*rays; //estructuras correpondientes a cada rayo

	unsigned int	strip[WIN_HEIGHT]; //buffer para proyectar las texturas
	
	unsigned int	timelastframe; //controla las frames/s del juego
} t_cub;

// ----------------------

//p_check_map.c
void	check_extension(char *argv1, t_cube *cube);
int		read_file(char *file, t_cube *cube);

//p_freedom.c
void	free_line(char *line, t_cube *cube);
void	free_content(t_cube *cube);
void	array_free(char **array);

//p_map_parsing
int		validate_map(t_cube *cube, t_player_position *player_position);

//p_parser.c
void	check_arg_number(int argc);
int		verification_start(t_cube *cube,\
			t_player_position *player_position, char **argv);
int		parser(int argc, char **argv);
void 	reach_last_character(const char *file_path);

//p_parsing.c
int		parse_line(char *line, t_cube *cube);
char	*line_verification(char *line);
int		parse_colors(char *line, int color[3]);
void	parse_map(char *line, t_cube *cube);

//p_util_map.c
void	delete_tab(char ***map, int i);
int		last_verification(t_cube *cube, t_player_position *player_position);
int		validate_file(t_cube *cube);

//p_utils.c
int		space_verification(char c);
int		array_len(char **array);
void 	error_exit();
int		is_number(const char *str);
void	set_initial_position(t_player_position *player_position, int x, int y,
		char orientation);
//print
char	*ft_sprintf(char const *container, ...);

// ----------------------

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

//process_player_input
int			process_player_input(void *param);
int			update_player_position(t_cub *c);
int			rotate_player(t_cub *c);
int			check_wall_collision(t_cub *c, float x, float y);

//ray_caster_scan_hits
void		find_horizontal_hit(t_cub *c, t_ray *r, float rayAngle);
void		find_horizontal_hit_loop(t_cub *c, t_ray *r);
void		find_vertical_hit(t_cub *c, t_ray *r, float rayAngle);
void		find_vertical_hit_loop(t_cub *c, t_ray *r);

//ray_caster
void		ray_caster(t_cub *c);
void		cast_ray(t_cub *c, t_ray *r, int ray_index, float rayAngle);
void		init_ray_struct(t_ray *r, int ray_index, float rayAngle);
void		select_ray_hit(t_cub *c, t_ray *r);

//ray_render
void		ray_render(t_cub *c);
int			init_data_render(t_cub *c, t_ray *r);
void		render(t_cub *c, t_ray *r);
void		draw_wall_strip(t_cub *c, int x);
void		calculate_wall_strip(t_cub *c, t_ray *r, t_texture *text, int x);

//utils
float		normalize_angle(float angle);
uint32_t	get_color(uint8_t *ptr);
uint32_t	get_color_alt(int *ptr);
int			has_wall_at(t_cub *c, float x, float y);
float		distance_between_points(float x1, float y1, float x2, float y2);

#endif