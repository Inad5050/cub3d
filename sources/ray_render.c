/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:21:58 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/24 17:38:02 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//int		mlx_pixel_put(t_xvar *xvar,t_win_list *win, int x,int y,int color)

void render_wall(t_cub *c, t_ray *r) // render the wall
{
	double wall_height;
	double bottom_pixel;
	double top_pixel;

	/* r->distance_medium *= cos(nor_angle(r->rayangle - c->p_rotationangle)); */ // fix the fisheye
	wall_height = (TILE_SIZE / /* r->distance_medium*/ r->distance) * ((WIN_WIDHT / 2) / tan(c->player_fov / 2)); // get the wall height
	bottom_pixel = (WIN_HEIGHT / 2) + (wall_height / 2); // get the bottom pixel. la pared estara centrada en la linea horizontal que forma el ecuador del eje Y. Esa linea esta en x = WINHEIGHT / 2. la pared tendra la misma altura por encima y por debajo
	top_pixel = (WIN_HEIGHT / 2) - (wall_height / 2); // get the top pixel
	if (bottom_pixel > WIN_HEIGHT) // check the bottom pixel. recuerda que el eje y crece hacia abajo
		bottom_pixel = WIN_HEIGHT;
	if (top_pixel < 0) // check the top pixel
		top_pixel = 0;
	
	/* printf("r->ray_index = %d\n", r->ray_index); */

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
			return (WHITE); // south wall
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
}
