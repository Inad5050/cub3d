/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:21:58 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/06 19:05:35 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	ray_render(t_cub *c)
{
	int		index_ray;
	t_ray	*r;

	index_ray = 0;
	while (index_ray < NUM_RAYS) //por cada rayo renderizalo
	{
		r = &c->rays[index_ray];
		init_data_render(c, r);
		render(c, r);
		draw_wall_strip(c, index_ray);
		if (r->is_sprite)
		{
			sprite_render(c, r);
			draw_sprite_strip(c, r, index_ray);
		}
		index_ray++;
	}
}

int	init_data_render(t_cub *c, t_ray *r) //inicializamos las variables que vamos a usar durante el renderizado
{
	if (r->distance == 0) //la distancia no puede ser 0, la ponemos a un minimo
		r->distance = 0.1;
	r->perp_distance = r->distance * cos(r->rayangle - c->p_rotationangle); //perp_distance es la distancia perpendicular desde el jugador hasta la pared golpeada por el rayo. Es una corrección necesaria para evitar la distorsión en la perspectiva causada por los rayos no perpendiculares. Todos los rayos salen desde el centro horizontal de la pantalla. Los rayos tienen un angulo que va desde -FOV/2 a FOV/2. Todos los rayos que no tengan un angulo de cero recorren más distancia de la necesaria para llegar hasta su pared. Esta variable es la distancia corregida.
	r->distance_proj_plane = (WIN_WIDHT / 2) / tan(c->p_fov / 2); //distance_proj_plane es la distancia desde la cámara del jugador hasta el plano de proyección, osease: (WIN_WIDHT / 2) el meridiano central de la patalla sobre el que se proyectaran todos los rayos. p_fov / 2 es el angulo del triangulo formado por el merdiano central (opuesto), la hipotenusa formada por el limite del FieldOfView, y el adyaccente, que sera la ditancia al plano de proyeccion
	r->wall_strip_height = (TILE_SIZE / r->perp_distance) * r->distance_proj_plane; //calcula la altura de la pared	
	r->wall_top_pixel = (WIN_HEIGHT / 2) - (r->wall_strip_height / 2); //calcula el punto mas alto de la pared desde el ecuador de la pantalla
	r->wall_bottom_pixel = (WIN_HEIGHT / 2) + (r->wall_strip_height / 2); //""
	return (0);
}

void	render(t_cub *c, t_ray *r) //identificamos la direccion cardinal del muro, y le adjudicamos su textura correspondiente
{	
	if (!r->was_hit_vertical)
	{
		if (r->rayangle < PI && r->rayangle > 0)
			calculate_wall_strip(c, r, c->wall_s, TILE_SIZE - 1 - ((int)(r->wall_hit_x + r->wall_hit_y) % TILE_SIZE)); //muro sur, el rayo viene desde abajo
		else
			calculate_wall_strip(c, r, c->wall_n, (int)(r->wall_hit_x + r->wall_hit_y) % TILE_SIZE); //muro norte
	}
	else
	{
		if (r->rayangle > PI * 1 / 2 && r->rayangle < PI * 3 / 2)
			calculate_wall_strip(c, r, c->wall_w, TILE_SIZE - 1 - ((int)(r->wall_hit_x + r->wall_hit_y) % TILE_SIZE)); //muro oeste, el rayo viene desde la derecha
		else 
			calculate_wall_strip(c, r, c->wall_e, (int)(r->wall_hit_x + r->wall_hit_y) % TILE_SIZE); //muro este
	}
}

//rellenamos strip[WIN_HEIGHT], un buffer con que almacenara los valores de los colores que vamos a imprimir sobre esta franja vertical (strip) de la pantalla, que correponde con el actual rayo 
//X es la coordenada X dentro del tile donde impactó el rayo. Su valor ira de 0 a TILE_SIZE
void	calculate_wall_strip(t_cub *c, t_ray *r, t_texture *t, int x)
{
	int	y;
	int	anti_y;
	int	img_x;
	int	img_y;

	y = 0;
	while (y < r->wall_top_pixel)
		c->strip[y++] = c->ceiling; //rellenamos la linea con el color del techo hasta el comienzo de la pared (el eje Y crece hacia abajo)
	img_x = 1;
	if (x != 1)
		img_x = (x * t->width) / TILE_SIZE; //es una regla de 3 entre la x relativa a TILE_SIZE y la relativa a el ancho de la imagen. img_x la columna de la textura que debe usarse para pintar la franja de la pared en pantalla.
	anti_y = y;
	if (r->wall_top_pixel < 0) //anti_y sirve para reducir el valor de y si el pixel más alto del muro se sale de la pantalla (porque estamos muy cerca), descontamos su valor de y para no empezar a imprimir hasta que hayamos aumentado img_y para compensar por la parte de la imagen que no tenemos que imprimir
		anti_y += r->wall_top_pixel;
	while (y < r->wall_bottom_pixel && y < WIN_HEIGHT) //el valor de y empieza en r->wall_top_pixel
	{
		img_y = ((y - anti_y) * t->height) / (r->wall_bottom_pixel - r->wall_top_pixel); //el valor de img_y solo cambia cada varias iteracciones de y. A un ritmo de t->height / (r->wall_bottom_pixel - r->wall_top_pixel). t->height (que es 128 para un PNG de 128 pixeles) es bastante más pequeño que (r->wall_bottom_pixel - r->wall_top_pixel)
		
/* 		if (r->ray_index == 0)
			printf("img_y %d = ((y %d - anti_y %d) * t->height %d) / (r->wall_bottom_pixel %d - r->wall_top_pixel %d)\n", img_y, y, anti_y, t->height, r->wall_bottom_pixel, r->wall_top_pixel);
 */
		if (img_y >= 0 && img_y < t->height && img_x >= 0 && img_x < t->width)
			c->strip[y++] = t->pixels[img_y][img_x];
	}
	while (y < WIN_HEIGHT)
		c->strip[y++] = c->floor;
}

void	draw_wall_strip(t_cub *c, int x)
{
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
		mlx_put_pixel(c->win_mlx3D, x, y, c->strip[y]);
}