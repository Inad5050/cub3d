/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:21:58 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/03 17:04:13 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ray_render(t_cub *c)
{
	int	index_ray;

	index_ray = 0;
	while (index_ray < NUM_RAYS) //por cada rayo renderizalo
	{
		init_data_render(c, &c->rays[index_ray]);
		render(c, &c->rays[index_ray]); //una vez conseguidas las dimensiones del rayo lo imprimimos en pantalla
		draw_wall_strip(c, index_ray);
		index_ray++;
	}
}

int	init_data_render(t_cub *c, t_ray *r) //inicializamos las variables que vamos a usar durante el renderizado
{
	if (r->distance == 0) //la distancia no puede ser 0, la ponemos a un minimo
		r->distance = 0.1;
	r->perp_distance = r->distance * cos(r->rayangle - c->p_rotationangle); //ajustamos la distancia desde la perspectiva del rayo a la del jugador (?)
	r->distance_proj_plane = (WIN_WIDHT / 2) / tan(c->p_fov / 2); //calculamos la distancia de la linea sobre la que vamos a proyectar los rayos
	r->wall_strip_height = (TILE_SIZE / r->perp_distance) * r->distance_proj_plane; //(?)
	r->wall_top_pixel = (WIN_HEIGHT / 2)	- (r->wall_strip_height / 2);
	r->wall_bottom_pixel = (WIN_HEIGHT / 2) + (r->wall_strip_height / 2);
	return (0);
}

void	render(t_cub *c, t_ray *r) //identificamos la direccion cardinal del muro
{
	if (!r->wasHitVertical)
	{
		if (r->rayangle < PI && r->rayangle > 0)
			calculate_wall_strip(c, r, c->wall_s, TILE_SIZE - 1 - ((int)(r->wallHitX + r->wallHitY) % TILE_SIZE)); //pasamos el tipo de muro y X, es la posicion del rayp (?)
		else
			calculate_wall_strip(c, r, c->wall_n, (int)(r->wallHitX + r->wallHitY) % TILE_SIZE);
	}
	else
	{
		if (r->rayangle > PI * 1 / 2 && r->rayangle < PI * 3 / 2)
			calculate_wall_strip(c, r, c->wall_w, TILE_SIZE - 1 - ((int)(r->wallHitX + r->wallHitY) % TILE_SIZE));
		else
			calculate_wall_strip(c, r, c->wall_e, (int)(r->wallHitX + r->wallHitY) % TILE_SIZE);
	}
}

void	draw_wall_strip(t_cub *c, int x)
{
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
		mlx_put_pixel(c->win_mlx3D, x, y, c->strip[y]);
}

void	calculate_wall_strip(t_cub *c, t_ray *r, t_texture *text, int x) //rellenamos strip(), es un buffer del contenido del rayo. //estoy usando t_img en lugar de t_texture
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
		img_x = (x * text->width) / TILE_SIZE; //calculamos el tamaño de cada linea de strip
	anti_y = y;
	if (r->wall_top_pixel < 0) //si el pixel más alto es negativo le restamos su valor a y (?)
		anti_y += r->wall_top_pixel;
	while (y < r->wall_bottom_pixel && y < WIN_HEIGHT)
	{
		img_y = ((y - anti_y) * text->height) / (r->wall_bottom_pixel - r->wall_top_pixel);
		if (img_y >= 0 && img_y < text->height && img_x >= 0 && img_x < text->width)
			c->strip[y++] = text->pixels[img_y][img_x];
	}
	while (y < WIN_HEIGHT)
		c->strip[y++] = c->floor;
}
