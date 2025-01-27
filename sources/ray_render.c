/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:21:58 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/27 20:09:26 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	render_strip(t_cub *c, int x)
{
	int	y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
		mlx_put_pixel(c->img, x, y, c->strip[y]);
}

void	get_strip(t_cub *c, t_ray *r, t_texture *text, int x) //rellenamos strip(), es un buffer del contenido del rayo. //estoy usando t_img en lugar de t_texture
{
	int	y;
	int	anti_y;
	int	img_x;
	int	img_y;

	y = 0;
	while (y < r->wall_top_pixel)
		c->strip[y++] = c->ceiling; //inicializamos strip como ceiling
	img_x = 1;
	if (x != 1)
		img_x = (x * text->width2) / TILE_SIZE; //calculamos el tamaño de cada linea de strip
	anti_y = y;
	if (r->wall_top_pixel < 0) //si el pixel más alto es negativo le restamos su valor a y (?)
		anti_y += r->wall_top_pixel;
	while (y < r->wall_bottom_pixel && y < WINDOW_HEIGHT)
	{
		img_y = ((y - anti_y) * text->height) / (r->wall_bottom_pixel - r->wall_top_pixel);
		if (img_y >= 0 && img_y < text->height && img_x >= 0 && img_x < text->width2)
			c->strip[y++] = text->img[img_y][img_x];
	}
	while (y < WINDOW_HEIGHT)
		c->strip[y++] = c->floor;
}

void	render(t_cub *c, t_ray *r) //identificamos la direccion cardinal del muro
{
	if (!r->wasHitVertical)
	{
		if (r->rayangle < PI && r->rayangle > 0)
			get_strip(c, r, c->wall_s, TILE_SIZE - 1 - ((int)(r->wallHitX + r->wallHitY) % TILE_SIZE)); //pasamos el tipo de muro y X, es la posicion del rayp (?)
		else
			get_strip(c, r, c->wall_n, (int)(r->wallHitX + r->wallHitY) % TILE_SIZE);
	}
	else
	{
		if (r->rayangle > PI * 1 / 2 && r->rayangle < PI * 3 / 2)
			get_strip(c, r, c->wall_w, TILE_SIZE - 1 - ((int)(r->wallHitX + r->wallHitY) % TILE_SIZE));
		else
			get_strip(c, r, c->wall_e, (int)(r->wallHitX + r->wallHitY) % TILE_SIZE);
	}
}

int	init_data_render(t_cub *c, t_ray *r) //inicializamos las variables que vamos a usar durante el renderizado
{
	if (r->distance == 0) //la distancia no puede ser 0, la ponemos a un minimo
		r->distance = 0.1;
	r->perp_distance = r->distance * cos(r->rayangle - c->p_rotationangle); //ajustamos la distancia desde la perspectiva del rayo a la del jugador (?)
	r->distance_proj_plane = (WINDOW_WIDTH / 2) / tan(c->player_fov / 2); //calculamos la distancia de la linea sobre la que vamos a proyectar los rayos
	r->wall_strip_height = (TILE_SIZE / r->perp_distance) * r->distance_proj_plane; //(?)
	r->wall_top_pixel = (WINDOW_HEIGHT / 2)	- (r->wall_strip_height / 2);
	r->wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (r->wall_strip_height / 2);
	return (0);
}

void	render_3d_projection(t_cub *c)
{
	int	index_ray;

	index_ray = 0;
	while (index_ray < NUM_RAYS) //por cada rayo renderizalo
	{
		init_data_render(c, &c->rays[index_ray]);
		render(c, &c->rays[index_ray]); //una vez conseguidas las dimensiones del rayo lo imprimimos en pantalla
		render_strip(c, index_ray);
		index_ray++;
	}
}




































//int		mlx_pixel_put(t_xvar *xvar,t_win_list *win, int x,int y,int color)

/* void render_wall(t_cub *c, t_ray *r) // render the wall
{
	double wall_height;
	double bottom_pixel;
	double top_pixel;

	r->distance_medium *= cos(nor_angle(r->rayangle - c->p_rotationangle)); // fix the fisheye
	wall_height = (TILE_SIZE / r->distance_medium r->distance) * ((WIN_WIDHT / 2) / tan(c->player_fov / 2)); // get the wall height
	bottom_pixel = (WIN_HEIGHT / 2) + (wall_height / 2); // get the bottom pixel. la pared estara centrada en la linea horizontal que forma el ecuador del eje Y. Esa linea esta en x = WINHEIGHT / 2. la pared tendra la misma altura por encima y por debajo
	top_pixel = (WIN_HEIGHT / 2) - (wall_height / 2); // get the top pixel
	if (bottom_pixel > WIN_HEIGHT) // check the bottom pixel. recuerda que el eje y crece hacia abajo
		bottom_pixel = WIN_HEIGHT;
	if (top_pixel < 0) // check the top pixel
		top_pixel = 0;
	
	printf("r->ray_index = %d\n", r->ray_index);

	draw_wall(c, r, top_pixel, bottom_pixel); // draw the wall
	draw_floor_ceiling(c, r->ray_index, top_pixel, bottom_pixel); // draw the floor and the ceiling
}

void draw_wall(t_cub *c, t_ray *r, int top_pixel, int bottom_pixel) // draw the wall
{
	int color;

	color = get_color(c, r, r->flag);
	while (top_pixel < bottom_pixel)
		my_mlx_pixel_put(c, r->ray_index, top_pixel++, color);
}

int get_color(t_cub *c, t_ray *r, int flag) // get the color of the wall
{
	r->rayangle = nor_angle(r->rayangle); // normalize the angle
	if (flag == 0) //'flag'. It is used to determine which angle I am facing to get the correct wall color.
	{
		if (r->rayangle > c->p_rotationangle / 2 && r->rayangle < 3 * (c->p_rotationangle / 2)) //la forma en la que determina en que pared estamos no la entiendo, pero parece algo aislado y estoy cansado de tantos angulos
			return (BLUE); // west wall
		else
			return (RED); // east wall
	}
	else
	{
		if (r->rayangle > 0 && r->rayangle < c->p_rotationangle)
			return (WHITE); // wall_suth wall
		else
			return (GREEN); // north wall
	}
}

void draw_floor_ceiling(t_cub *c, int ray, int top_pixel, int bottom_pixel) // draw the floor and the ceiling
{
 	int  i;

	i = bottom_pixel;
	while (i < WIN_HEIGHT)
		my_mlx_pixel_put(c, ray, i++, PURPLE); // floor
	i = 0;
	while (i < top_pixel)
		my_mlx_pixel_put(c, ray, i++, ORANGE); // ceiling
} */
