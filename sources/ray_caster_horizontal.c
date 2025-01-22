/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_horizontal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:19:39 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/22 18:19:37 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	find_horizontal_hit(t_cub *c, t_ray *r, float rayAngle, int stripid)
{
	//CURSO find the y coordinate of the closest horizontal grid intersection
	
	r->yintercept = floor(c->p_y / TILE_SIZE) * TILE_SIZE; //TILE_SIZE se inicializa como 2000 el mismo valor del WIN_WIDTH. player.y son las coordenadas del jugador
	//r->yintercept += r->isRayFacingDown ? TILE_SIZE : 0; 
	//? : es el operador ternario "condición ? valor_si_es_verdadero : valor_si_es_falso;"
	//el equivalente seria:
	if (r->isRayFacingDown)
		r->yintercept += TILE_SIZE;
	//cuando calculamos la coordenada Y de la siguiente interseccion horizontal sabemos exactamente cual va a ser el valor de y. va a ser la y de la siguiente celda a la actual ubicacion del jugador. al ser la intersección HORIZONTAL es por fuerza mayor la siguiente. En funcion de la direccion del rayo redondeamos hacia abajo (hasta un numero entero) el valor de la posicion del jugador o redondeamos hacia abajo el valor de la posicion y le sumamos el valor de una casilla del mapa
		
	//CURSO find the x coordinate of the closest horizontal grid intersection
	
	r->xintercept = c->p_x + (r->yintercept - c->p_y) / tan(rayAngle);
	//teniendo el lado y del triangulo tenemos el lado opuesto del angulo del rayo. Usando la tangente (tan = opuesto / adyacente) -> adyacente = opuesto / tan. 

	//CURSO calculate the increment xstep and ystep.
	
	//codigo original : r->ystep *= r->isRayFacingUp ? -1 : 1;
	r->ystep = TILE_SIZE; //la distancia que se recorre en el vector Y para cruzar de un rectangulo a otro
	if (r->isRayFacingUp)
		r->ystep *= -1;
		
	r->xstep = TILE_SIZE / tan(rayAngle); //la distancia que se recorre en el vector X para cruzar de un rectangulo a otro
	//codigo original :
		//r->xstep *= r->isRayFacingLeft && r->xstep > 0 ? -1 : 1;
		//r->xstep *= r->isRayFacingRight && r->xstep < 0 ? -1 : 1;
	if (r->isRayFacingLeft && r->xstep > 0)
		r->xstep *= -1;
	if (r->isRayFacingRight && r->xstep < 0)
		r->xstep *= -1;
	find_horizontal_hit_loop(c, r, rayAngle, stripid);
}

void	find_horizontal_hit_loop(t_cub *c, t_ray *r, float rayAngle, int stripid)
{
	//vamos a aumentar la longitud del rayo progresivamente. Cada vez cruzara TILE_SIZE distancia en el eje Y. Asi obtendremos todos los puntos de corte horizontales. En cada punto de corte comprobaremos si la siguiente celda tiene una pared.
	//Debemos empezar por el principio en el eje Y de una celda. Por lo que nuestro punto de partida es el primer punto de corte que ya hemos calculado: xintercept e yintercept
	r->nextHorzTouchX = r->xintercept;
	r->nextHorzTouchY = r->yintercept;

	while(r->nextHorzTouchX >= 0 && r->nextHorzTouchX <= WIN_WIDHT \
	&& r->nextHorzTouchY >= 0 && r->nextHorzTouchY <= WIN_HEIGHT)
	{
		r->xToCheck = r->nextHorzTouchX;
		r->yToCheck = r->nextHorzTouchY; //lo ajustamos para estar en el proximo cuadrado y no en el borde de la interseccion
		if (r->isRayFacingUp)
			r->yToCheck - 1;
		if (mapHasWallAt(c, r->xToCheck, r->yToCheck)) //ME FALTA LA FUNCION
		{
			//encontramos muro
			r->horizontalWallHitX = r->nextHorzTouchX; 
			r->horizontalWallHitY = r->nextHorzTouchY;
			r->horizontalWallContent = c->map[(int)floor(r->yToCheck / TILE_SIZE)][(int)floor(r->xToCheck / TILE_SIZE)];	
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
