/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_scan_hits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:19:39 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/06 17:45:24 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	find_horizontal_hit(t_cub *c, t_ray *r, float rayAngle) //FCD
{
	r->found_horizontal_wall_hit = 0;
	r->horizontal_wall_hit_x = 0;
	r->horizontal_wall_hit_y = 0;
	r->horizontal_wall_content = 0;
	
	r->yintercept = floor(c->p_y / TILE_SIZE) * TILE_SIZE; //la interseccion del rayo con el borde de nuestra celda. Redondeamos el valor de la posicion del jugador hacia abajo para obtener la posicion del limite de su casilla actual. El valor de TILE_SIZE es arbitrario, es el numero de veces en el que dividimos cada celda. 
	if (r->isRayFacingDown)
		r->yintercept += TILE_SIZE;
	r->xintercept = c->p_x + (r->yintercept - c->p_y) / tan(rayAngle); //teniendo el lado adyacente (r->yintercept) del triangulo recto formado por el angulo del rayo tambien tenemos el lado opuesto. Usando la tangente (tan = opuesto / adyacente) -> adyacente = opuesto / tan.
	r->ystep = TILE_SIZE; //la distancia que se recorre en el vector Y para cruzar de un rectangulo a otro. Cuando calculamos el valor Y de la siguiente celda (la siguiente interseccion horizontal) sabemos que entre el comienzo de una celda y otra hay TILE_SIZE de distancia.
	if (r->isRayFacingUp)
		r->ystep *= -1;
	r->xstep = TILE_SIZE / tan(rayAngle); //la distancia que se recorre en el vector X para cruzar de un rectangulo a otro
	if (r->isRayFacingLeft && r->xstep > 0)
		r->xstep *= -1;
	if (r->isRayFacingRight && r->xstep < 0)
		r->xstep *= -1;
	find_horizontal_hit_loop(c, r);
}


//debemos empezar al principio del eje Y de una celda. Por lo que nuestro punto de partida es el primer punto de corte que ya hemos calculado: xintercept e yintercept
//vamos a aumentar la longitud del rayo progresivamente. Cada vez cruzara TILE_SIZE distancia en el eje Y. Asi obtendremos todos los puntos de corte horizontales. En cada punto de corte comprobaremos si la siguiente celda tiene una pared.
void	find_horizontal_hit_loop(t_cub *c, t_ray *r)
{
	r->next_horz_touch_x = r->xintercept;
	r->next_horz_touch_y = r->yintercept;
	while(r->next_horz_touch_x >= 0 && r->next_horz_touch_x <= c->map_max_x \
	&& r->next_horz_touch_y >= 0 && r->next_horz_touch_y <= c->map_max_y)
	{
		r->x_to_check = r->next_horz_touch_x;
		r->y_to_check = r->next_horz_touch_y; //lo ajustamos para estar en el proximo cuadrado y no en el borde de la interseccion
		if (r->isRayFacingUp)
			r->y_to_check -= 1;
		if (has_wall_at(c, r->x_to_check, r->y_to_check))
		{
			r->horizontal_wall_hit_x = r->next_horz_touch_x; 
			r->horizontal_wall_hit_y = r->next_horz_touch_y;
			r->found_horizontal_wall_hit = TRUE;
			break;		
		}
		else
		{
			r->next_horz_touch_x += r->xstep;
			r->next_horz_touch_y += r->ystep;
		}
	}
}

void	find_vertical_hit(t_cub *c, t_ray *r, float rayAngle) //FCD
{
	r->found_vertical_wall_hit = 0;
	r->vertical_wall_hit_x = 0;
	r->vertical_wall_hit_y = 0;
	r->vertical_wall_content = 0;
	r->xintercept = floor(c->p_x / TILE_SIZE) * TILE_SIZE;
	if (r->isRayFacingRight)
		r->xintercept += TILE_SIZE;
	r->yintercept = c->p_y + (r->xintercept - c->p_x) * tan(rayAngle);
	r->xstep = TILE_SIZE;
	if (r->isRayFacingLeft)
		r->xstep *= -1;
	r->ystep = TILE_SIZE * tan(rayAngle);
	if (r->isRayFacingUp && r->ystep > 0)
		r->ystep *= -1;
	else if (r->isRayFacingDown && r->ystep < 0)
		r->ystep *= -1;
	find_vertical_hit_loop(c, r);
}

void	find_vertical_hit_loop(t_cub *c, t_ray *r)
{
	r->next_vertical_touch_x = r->xintercept;
	r->next_vertical_touch_y = r->yintercept;
	while(r->next_vertical_touch_x >= 0 && r->next_vertical_touch_x <= c->map_max_x \
	&& r->next_vertical_touch_y >= 0 && r->next_vertical_touch_y <= c->map_max_y)
	{
		r->x_to_check = r->next_vertical_touch_x;
		if (r->isRayFacingLeft)
			r->x_to_check -= 1;
		r->y_to_check = r->next_vertical_touch_y;
		if (has_wall_at(c, r->x_to_check, r->y_to_check)) 
		{
			r->vertical_wall_hit_x = r->next_vertical_touch_x; 
			r->vertical_wall_hit_y = r->next_vertical_touch_y;
			r->found_vertical_wall_hit = TRUE;
			break;		
		}
		else
		{
			r->next_vertical_touch_x += r->xstep;
			r->next_vertical_touch_y += r->ystep;
		}
	}
}

int	has_wall_at(t_cub *c, float x, float y) //detecta si la coordenada es suelo u otro elemento
{
	int		map_grid_index_x;
	int		map_grid_index_y;
	char	tile;

	map_grid_index_x = ((int)x / TILE_SIZE); //cuando casteamos un float a int perdemos los valores decimales, redondeando el valor de las coordenadas al borde de la casilla actual
	map_grid_index_y = ((int)y / TILE_SIZE);
	if (map_grid_index_y < 0 || map_grid_index_y >= c->map_max_y) //comprobamos que las coordenadas no se salgan del mapa
		return (0);
	if (map_grid_index_x < 0 || 
	map_grid_index_x >= (int)ft_strlen(c->map[map_grid_index_y]))
		return (0);
	tile = c->map[map_grid_index_y][map_grid_index_x];
	return (tile != '0'); //si la casilla de las coordenadas no es suelo devolvemos 1
}
