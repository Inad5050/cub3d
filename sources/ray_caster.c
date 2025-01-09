/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
 /*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:55:21 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/08 15:59:44 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ray_direction(t_cub *c)
{
	printf("RAY_DIRECTION\n");
	
	int	ray_index; //indice del rayo en la pantalla, iremos creando rayos verticales (sobre el eje x) hasta cubrir la anchura("0 ray_index = %d\n", ray_index);

	ray_index = 0;
/* 	while (ray_index < WIN_WIDHT)
	{ */
		c->ray_camera = 2 * ray_index / (double)WIN_WIDHT - 1; //camera_x varia entre -1 (izq del todo) y 1 (derecha del todo). SI es 0 está en el centro
		printf("c->ray_camera %lf = 2 * ray_index %d / (double)WIN_WIDHT %lf - 1\n", c->ray_camera, ray_index, (double)WIN_WIDHT - 1);
		
		c->ray_dx = c->p_dx + c->plane_x * c->ray_camera;
		printf("c->ray_dx %lf = c->p_dx %lf + c->plane_x %lf * c->ray_camera %lf\n", c->ray_dx, c->p_dx, c->plane_x, c->ray_camera);
		
		c->ray_dy = c->p_dy + c->plane_y * c->ray_camera;
		printf("c->ray_dy %lf = c->p_dy %lf + c->plane_y %lf * c->ray_camera %lf\n", c->ray_dy, c->p_dy, c->plane_y, c->ray_camera);
	
		delta_distance(c);
		initial_distance(c);
		digital_differential_analysis(c);
		wall_distance(c);
/* 		ray_index++;
	} */
}

//fabs() valor absoluto de un punto flotante (decimal)

void	delta_distance(t_cub *c)
{
	printf("DELTA_DISTANCE\n");
	c->map_x = (int)(c->p_x);
	printf("c->map_x %d = (int)(c->p_x) %d\n", c->map_x, (int)(c->p_x));
	c->map_y = (int)(c->p_y);
	printf("c->map_y %d = (int)(c->p_y) %d\n", c->map_y, (int)(c->p_y));
	c->delta_dist_x = fabs(1 / c->ray_dx);
	printf("c->delta_dist_x %lf = fabs(1 / c->ray_dx %lf);\n", c->delta_dist_x, c->ray_dx);
	c->delta_dist_y = fabs(1 / c->ray_dy);
	printf("c->delta_dist_y %lf = fabs(1 / c->ray_dy %lf);\n", c->delta_dist_y, c->ray_dy);
}

/* Mientras que c->ray_dx y c->ray_dy definen la dirección exacta en la que se lanza el rayo, 
step_x y step_y indican el sentido en el que el rayo debe avanzar en la cuadrícula del mapa (hacia la izquierda o derecha en el eje x,
y hacia arriba o abajo en el eje y). Cada uno solo puede ser 1 o -1. */

/* c->p_dx delta x del jugador en el mapa, map_x posición de la siguiente celda, 
delta_dist_x distancia hasta la siguiente celda */

//c->side_dist_x y c->side_dist_y son la distancia hasta el siguiente rectangulo

void	initial_distance(t_cub *c)
{
	printf("INITIAL_DISTANCE\n");
	
	if (c->ray_dx < 0)
	{
		c->step_x = -1;
		c->side_dist_x = (c->p_dx - c->map_x) * c->delta_dist_x;
	}
	else
	{
		c->step_x = 1;
		c->side_dist_x = (c->map_x + 1.0 - c->p_dx) * c->delta_dist_x;
	}
	if (c->ray_dy < 0)
	{
		c->step_y = -1;
		c->side_dist_y = (c->p_dy - c->map_y) * c->delta_dist_y;
	}
	else
	{
		c->step_y = 1;
		c->side_dist_y = (c->map_y + 1.0 - c->p_dy) * c->delta_dist_y;
	}

	printf("c->step_x = %d c->step_y %d\n", c->step_x, c->step_y);
}

void	digital_differential_analysis(t_cub *c)
{
	while (42)
	{
		printf("DIGITAL_DIFFERENTIAL_ANALYSIS\n");

		if (c->side_dist_x < c->side_dist_y)
		{
			printf("c->side_dist_x %lf < c->side_dist_y %lf\n", c->side_dist_x, c->side_dist_y);
			c->side_dist_x += c->delta_dist_x;
			printf("c->side_dist_x %lf += c->delta_dist_x %lf \n", c->side_dist_x, c->delta_dist_x);
			c->map_x += c->step_x;
			printf("c->map_x %d < c->step_x %d\n", c->map_x, c->step_x);
			c->side = 0;
			printf("c->side %d\n", c->side);
		}
		else
		{
			printf("c->side_dist_y %lf < c->side_dist_y %lf\n", c->side_dist_y, c->side_dist_y);
			c->side_dist_y += c->delta_dist_y;
			printf("c->side_dist_y %lf += c->delta_dist_y %lf \n", c->side_dist_y, c->delta_dist_y);
			c->map_y += c->step_y;
			printf("c->map_y %d < c->step_y %d\n", c->map_y, c->step_y);
			c->side = 1;
			printf("c->side %d\n", c->side);
		}

		if (c->map[(int)c->map_y / CELL_HEIGHT][(int)c->map_x / CELL_WIDHT] == '1')
			break;
/* 		if (c->map[(int)floor(c->map_y / CELL_HEIGHT)][(int)floor(c->map_x / CELL_WIDHT)] == '1')
			break; */
	}
	
	if (c->side_dist_x < c->side_dist_y)
		{
			printf("c->side_dist_x %lf < c->side_dist_y %lf\n", c->side_dist_x, c->side_dist_y);
			printf("c->side_dist_x %lf += c->delta_dist_x %lf \n", c->side_dist_x, c->delta_dist_x);
			printf("c->map_x %d < c->step_x %d\n", c->map_x, c->step_x);
			printf("c->side %d\n", c->side);
		}
	else
		{
			printf("c->side_dist_y %lf < c->side_dist_y %lf\n", c->side_dist_y, c->side_dist_y);
			printf("c->side_dist_y %lf += c->delta_dist_y %lf \n", c->side_dist_y, c->delta_dist_y);
			printf("c->map_y %d < c->step_y %d\n", c->map_y, c->step_y);
			printf("c->side %d\n", c->side);
		}
	printf("c->map[%d][%d]\n", (int)c->map_y / CELL_HEIGHT, (int)c->map_x / CELL_WIDHT);

}

void	wall_distance(t_cub *c)
{
	printf("WALL_DISTANCE\n");

	if (c->side == 0)
		c->wall_dist = (c->map_x - c->p_x + (1 - c->step_x) / 2) / c->ray_dx;
	else
		c->wall_dist = (c->map_y - c->p_y + (1 - c->step_y) / 2) / c->ray_dy;
	c->line_height = (int)(WIN_HEIGHT / c->wall_dist);
	c->draw_start = (int)(-c->line_height / 2 + WIN_HEIGHT / 2);
	if (c->draw_start < 0)
		c->draw_start = 0;
	c->draw_end = (int)(c->line_height / 2 + WIN_HEIGHT / 2);
	if (c->draw_end >= WIN_HEIGHT)
		c->draw_end = WIN_HEIGHT - 1;
	if (c->side == 0)
		c->wall_height = c->p_y + c->wall_dist * c->ray_dx; //en el codigo original aparece ray->dy he interpretado que es lo mismo que c->ray_dx, aunque no estoy seguro
	else
		c->wall_height = c->p_x + c->wall_dist * c->ray_dy;
	c->wall_height -= floor(c->wall_height);

	printf("c->wall_height = %lf\n\n", c->wall_height);
}
