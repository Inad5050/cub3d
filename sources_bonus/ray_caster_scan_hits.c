/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_scan_hits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:19:39 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/04 15:16:21 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	find_horizontal_hit(t_cub *c, t_ray *r, float rayAngle) //FCD
{
	r->foundHorizontalWallHit = 0;
	r->horizontalWallHitX = 0;
	r->horizontalWallHitY = 0;
	r->horizontalWallContent = 0;
	
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
	r->nextHorzTouchX = r->xintercept;
	r->nextHorzTouchY = r->yintercept;
	while(r->nextHorzTouchX >= 0 && r->nextHorzTouchX <= c->map_max_x \
	&& r->nextHorzTouchY >= 0 && r->nextHorzTouchY <= c->map_max_y)
	{
		r->xToCheck = r->nextHorzTouchX;
		r->yToCheck = r->nextHorzTouchY; //lo ajustamos para estar en el proximo cuadrado y no en el borde de la interseccion
		if (r->isRayFacingUp)
			r->yToCheck -= 1;
		if (has_wall_at(c, r->xToCheck, r->yToCheck))
		{
			r->horizontalWallHitX = r->nextHorzTouchX; 
			r->horizontalWallHitY = r->nextHorzTouchY;
			r->foundHorizontalWallHit = TRUE;
			break;		
		}
		else
		{
			r->nextHorzTouchX += r->xstep;
			r->nextHorzTouchY += r->ystep;
		}
	}
}

void	find_vertical_hit(t_cub *c, t_ray *r, float rayAngle) //FCD
{
	r->foundVerticalWallHit = 0;
	r->verticalWallHitX = 0;
	r->verticalWallHitY = 0;
	r->verticalWallContent = 0;
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
	r->nextVerticalTouchX = r->xintercept;
	r->nextVerticalTouchY = r->yintercept;
	while(r->nextVerticalTouchX >= 0 && r->nextVerticalTouchX <= c->map_max_x \
	&& r->nextVerticalTouchY >= 0 && r->nextVerticalTouchY <= c->map_max_y)
	{
		r->xToCheck = r->nextVerticalTouchX;
		if (r->isRayFacingLeft)
			r->xToCheck -= 1;
		r->yToCheck = r->nextVerticalTouchY;
		if (has_wall_at(c, r->xToCheck, r->yToCheck)) 
		{
			r->verticalWallHitX = r->nextVerticalTouchX; 
			r->verticalWallHitY = r->nextVerticalTouchY;
			r->foundVerticalWallHit = TRUE;
			break;		
		}
		else
		{
			r->nextVerticalTouchX += r->xstep;
			r->nextVerticalTouchY += r->ystep;
		}
	}
}
