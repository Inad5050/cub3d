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
	int	ray_index; //indice del rayo en la pantalla, iremos creando rayos hasta cubrir la anchura de la pantalla

	ray_index = 0;
	while (ray_index < WIN_WIDHT)
	{
		c->ray_camera = 2 * ray_index / (double)WIN_WIDHT - 1; //camera_x varia entre -1 (izq del todo) y 1 (derecha del todo). SI es 0 está en el centro
		c->ray_dx = c->p_dx + c->plane_x * c->ray_camera;
		c->ray_dy = c->p_dy + c->plane_y * c->ray_camera;

		//..

		delta_distance(c); //va aqui?
		ray_index++; //necesario?
	
	}
}

void	delta_distance(t_cub *c)
{
	c->delta_dist_x = fabs(1 / c->ray_dx); //fabs() valor absoluto de un punto flotante (decimal)
	c->delta_dist_y = fabs(1 / c->ray_dy);
	steps(c);
}

//Mientras que c->ray_dx y c->ray_dy definen la dirección exacta en la que se lanza el rayo, step_x y step_y indican el \
sentido en el que el rayo debe avanzar en la cuadrícula del mapa (hacia la izquierda o derecha en el eje x, \
y hacia arriba o abajo en el eje y). Cada uno solo puede ser 1 o -1.

void	steps(t_cub *c)
{
	double	map_x;
	double	map_y;

	map_x = root(c->p_x);
	map_y = root(c->p_y);
	if (c->ray_dx < 0)
	{
		c->step_x = -1;
		c->side_dist_x = (c->p_dx - map_x) * c->delta_dist_x; //c->p_dx coordenadas del jugador en el mapa, map_x posición de la siguiente celda, distancia hasta la siguiente celda delta_dist_x
	}
	else
	{
		c->step_x = 1;
		c->side_dist_x = (map_x + 1.0 - c->p_dx) * c->delta_dist_x;
	}
	if (c->ray_dy < 0)
	{
		c->step_y = -1;
		c->side_dist_y = (c->p_dy - map_y) * c->delta_dist_y;
	}
	else
	{
		c->step_y = 1;
		c->side_dist_y = (map_y + 1.0 - c->p_dy) * c->delta_dist_y;
	}
}

