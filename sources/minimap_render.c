/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:55:44 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/05 16:12:51 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	minimap_render(t_cub *c)
{
/* 	int		y;
	int		x;
	char	element; */

	init_minimap(c);
/* 	y = 0;
	while (y < c->map_max_y)
	{
		x = 0;
		while (x < c->map_max_x)
		{
			element = c->map[y][x];
			if (element == '0')
				minimap_print(x, y, BLUE);
			if (element == '1')
				minimap_print(x, y, WHITE);
			if (element == 'N' || element == 'S'
			 || element == 'E' || element == 'W')
				minimap_print(x, y, GREEN);				
			x++;
		}
		y++;
	} */	
}

/* void	minimap_print(x, y, element)
{
	



	
} */

void	init_minimap(t_cub *c)
{
	int	y;
	int	x;

	y = WIN_HEIGHT * 0.01;
	c->minimap_area_x = 0.3 * WIN_HEIGHT;
	c->minimap_area_y = 0.3 * WIN_HEIGHT;
	c->minimap_tile_size = c->minimap_area_x / (c->map_max_x / TILE_SIZE);
	if (c->minimap_area_y / (c->map_max_y / TILE_SIZE) < c->minimap_tile_size)  
		c->minimap_tile_size = c->minimap_area_y / (c->map_max_y / TILE_SIZE);
	
	printf("c->minimap_area_y = %d c->minimap_tile_size = %d c->minimap_area_x %d\n", c->minimap_area_y, c->minimap_tile_size, c->minimap_area_x);
	
	
	while (y < c->minimap_area_y)
	{
		x = WIN_WIDHT * 0.01;
		while (x < c->minimap_area_x + WIN_WIDHT * 0.05)
		{
			mlx_put_pixel(c->win_mlx3D, x, y, WHITE);
			x++;
		}
		y++;
	}
}

/* void	calculate_wall_strip(t_cub *c, t_ray *r, t_texture *t, int x)
{
	int	y;
	int	anti_y;
	int	img_x;
	int	img_y;

	y = 0;
	while (y < r->wall_top_pixel)
		c->strip[y++] = c->ceiling; //rellenamos la linea con el color del techo hasta el comienzo de la pared (el eje y crece hacia abajo)
	img_x = 1;
	if (x != 1)
		img_x = (x * t->width) / TILE_SIZE; //es una regla de 3 entre la x relativa a TILE_SIZE y la relativa a el ancho de la imagen. img_x la columna de la textura que debe usarse para pintar la franja de la pared en pantalla.
	anti_y = y;
	if (r->wall_top_pixel < 0) //anti_y sirve para reducir el valor de y si el pixel más alto del muro se sale de la pantalla (porque estamos muy cerca), descontamos su valor de y para no empezar a imprimir hasta que hayamos aumentado img_y para compensar por la parte de la imagen que no tenemos que imprimir
		anti_y += r->wall_top_pixel;
	while (y < r->wall_bottom_pixel && y < WIN_HEIGHT) //el valor de y empieza en r->wall_top_pixel
	{
		img_y = ((y - anti_y) * t->height) / (r->wall_bottom_pixel - r->wall_top_pixel); //el valor de img_y solo cambia cada varias iteracciones de y. A un ritmo de t->height / (r->wall_bottom_pixel - r->wall_top_pixel). t->height (que es 128 para un PNG de 128 pixeles) es bastante más pequeño que (r->wall_bottom_pixel - r->wall_top_pixel)
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
} */