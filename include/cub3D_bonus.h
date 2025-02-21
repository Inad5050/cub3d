/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/21 17:55:49 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../mlx/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <math.h>
# include <limits.h>
# include <stdint.h>

//sizes
# define WIN_WIDTH 2000
# define WIN_HEIGHT 1000
# define PLAYER_SIZE 10
# define PI 3.14159265
# define ANGLE_ROTATION_SIZE 5
# define MOVESPEED_MOD 10
# define FRAMES 30 
# define TILE_SIZE 1000
# define NUM_RAYS WIN_WIDTH

//bools
# define FALSE 0
# define TRUE 1

//colors
# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF

//doors
# define OPEN_TIME 20
# define OPEN_DISTANCE 2000
# define DOOR_ROUTE "./texture/doom_door.png"

typedef struct s_player_position
{
	int				x;
	int				y;
	int				pos_x;
	int				pos_y;
	char			orientation;
}					t_player_position;

typedef struct s_cube
{
	char			**map;
	int				player_x;
	int				player_y;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	int				floor_color[3];
	int				ceiling_color[3];
	int				max_y_size;
	int				max_x_size;
	char			*raw_map;
}					t_cube;

typedef struct s_door
{
	int				x_door;
	int				y_door;
	int				is_closed;
	int				opening;
	int				closing;
}	t_door;

typedef struct s_texture
{
	int				width;
	int				height;
	unsigned int	**pixels;
}	t_texture;

typedef struct s_ray
{
	float			rayangle;
	int				ray_index;

	int				israyfacingdown;
	int				israyfacingup;
	int				israyfacingleft;
	int				israyfacingright;

	float			xintercept;
	float			yintercept;

	float			xstep;
	float			ystep;

	float			next_horz_touch_x;
	float			next_horz_touch_y;
	float			next_vertical_touch_x;
	float			next_vertical_touch_y;
	float			x_to_check;
	float			y_to_check;

	float			horizontal_wall_hit_x;
	float			horizontal_wall_hit_y;
	char			horizontal_wall_content;
	int				found_horizontal_wall_hit;
	float			vertical_wall_hit_x;
	float			vertical_wall_hit_y;
	char			vertical_wall_content;
	int				found_vertical_wall_hit;

	float			horizontal_hit_distance;
	float			vertical_hit_distance;

	float			distance;
	float			wall_hit_x;
	float			wall_hit_y;
	float			was_hit_vertical;

	float			perp_distance;
	float			distance_proj_plane;
	float			wall_strip_height;
	int				wall_top_pixel;
	int				wall_bottom_pixel;
	unsigned int	wall_color;

	int				im_door;
	int				door_number;

	int				img_x;
	int				img_y;
}	t_ray;

typedef struct s_cub
{
	void			*mlx;
	mlx_image_t		*win_mlx3d;

	t_cube			*parse_struct;

	char			**map;
	int				player_direction;
	int				map_max_y;
	int				map_max_x;

	unsigned int	ceiling;
	unsigned int	floor;
	t_texture		*wall_n;
	t_texture		*wall_s;
	t_texture		*wall_w;
	t_texture		*wall_e;
	t_texture		*door_t;

	float			p_fov;
	float			p_turnspeed;
	float			p_walkspeed;
	float			p_turnspeed_original;

	float			p_rotationangle;
	float			p_y;
	float			p_x;

	int				p_walkdirection;
	int				p_strafedirection;
	int				p_turndirection;

	t_ray			*rays;

	unsigned int	strip[WIN_HEIGHT];

	unsigned int	timelastframe;

	float			minimap_start_y;
	float			minimap_start_x;
	float			minimap_area_y;
	float			minimap_area_x;
	float			minimap_tile_size;
	float			minimap_player_size;

	t_door			*doors;
	int				door_number;
	int				door_closing;
	int				map_grid_index_x;
	int				map_grid_index_y;
}					t_cub;

//doors_aux
int			detect_doors_aux(t_cub *c, t_ray *r, t_door *d);

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
void		free_t_texture(t_texture *t);

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
void		init_minimap(t_cub *c);

void		check_extension(char *argv1);
int			read_file(char *file, t_cube *cube);

void		free_line(char *line, t_cube *cube);
void		free_content(t_cube *cube);
void		array_free(char **array);

int			validate_map(t_cube *cube, t_player_position *player_position);

void		check_arg_number(int argc);
int			verification_start(t_cube *cube, \
			t_player_position *player_position, char **argv);
int			parser(int argc, char **argv);
void		reach_last_character(const char *file_path);

int			parse_line(char *line, t_cube *cube);
char		*line_verification(char *line);
int			parse_colors(char *line, int color[3]);
void		parse_map(char *line, t_cube *cube);

void		delete_tab(char ***map, int i);
int			last_verification(t_cube *cube, t_player_position *player_position);
int			validate_file(t_cube *cube);

int			space_verification(char c);
int			array_len(char **array);
void		error_exit(void);
int			is_number(const char *str);
void		set_initial_position(t_player_position *player_position, int x, \
				int y, char orientation);

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

//ray_render_aux
void		draw_wall_strip(t_cub *c, int x);

//ray_render
void		ray_render(t_cub *c);
int			init_data_render(t_cub *c, t_ray *r);
void		render(t_cub *c, t_ray *r);
void		render_aux(t_cub *c, t_ray *r);
void		calculate_wall_strip(t_cub *c, t_ray *r, t_texture *text, int x);

//utils
float		normalize_angle(float angle);
uint32_t	get_color(uint8_t *ptr);
uint32_t	get_color_alt(int *ptr);
float		distance_between_points(float x1, float y1, float x2, float y2);

#endif