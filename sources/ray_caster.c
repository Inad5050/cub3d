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

/* 
Todos los rayos empiezan en la posición del jugador y se esparcen en todas direcciones a lo largo de la pantalla. Hay tantos rayos como pixeles en el eje X de la pantalla del juego (WIN_WIDHT), ese es literalmente numero maximo de direcciones posibles. Proyectaremos un rayo desde el jugador a cada uno de esos pixeles.
El jugador puede ver 60 grados (lo habitual en juegos 3D). Esa "camara" va cambiando a medida que el jugador se desplaza sobre el mapa 2D y a medida que el jugador rota el angulo de su orientación sobre los ejes X, Y del mapa 2D. 
c->camera_x y c->camera_y: en init_game calculamos los ejes de esa camara. Se calculan como las tangentes de los componentes X e Y del angulo actual del jugador sobre los ejes del mapa.
c->relative_ray_index: indice relativo a la anchura de la camara (WIN_WIDHT) de los rayos que vamos a proyectar. Su valor va desde -1 a 1.
c->ray_dx y c->ray_dy: son la delta del angulo del rayo. Hereda el angulo del jugador, acrecentado por por su propio angulo relativo a la camara. De forma que cada rayo en pantalla tendra su propio angulo para llegar al pixel (de entre los 1300 de WIN_WIDHT) que tiene que alcanzar.
*/
void	ray_direction(t_cub *c) 
{	
	int	ray_index; //indice del rayo en la pantalla, iremos creando rayos verticales (sobre el eje x) hasta cubrir la anchura("0 x = %d\n", x);

	ray_index = 0;
/* 	while (ray_index < WIN_WIDHT) //por cada uno de los 1300 bytes del juego en el eje x proyectamos un rayo
	{ */
		c->relative_ray_index = (2 * ray_index / (double)WIN_WIDHT) - 1; //ray_camera varia entre -1 (izq del todo) y 1 (derecha del todo). Si es 0 está en el centro
		c->ray_dx = c->p_angle_x + c->camera_x * c->relative_ray_index;
		c->ray_dy = c->p_angle_y + c->camera_y * c->relative_ray_index;
		
/* 		printf("RAY_DIRECTION\n");
		printf("x = %d\n", ray_index);
		printf("c->ray_index = (2 * x / (double)WIN_WIDHT) - 1 \n%lf = (2 * %d / %lf) - 1\n", c->relative_ray_index, ray_index, (double)WIN_WIDHT - 1);
		printf("c->ray_dx = c->p_angle_x + c->camera_x * c->relative_ray_index \n%lf = %lf + %lf * %lf\n", c->ray_dx, c->p_angle_x, c->camera_x, c->relative_ray_index);
		printf("c->ray_dy = c->p_angle_y + c->camera_y * c->relative_ray_index \n%lf = %lf + %lf * %lf\n", c->ray_dy, c->p_angle_y, c->camera_y, c->relative_ray_index);
		printf("\n"); */

		delta_distance(c);
		initial_distance(c);
		digital_differential_analysis(c);
		wall_distance(c);
/* 		ray_index++;
	} */
}

//fabs() valor absoluto de un punto flotante (decimal)
//c->delta_dist_x y c->delta_dist_y son la distancia relativa (relativa a CELL_WIDHT y CELL_HEIGHT) que el rayo debera recorrer con su angulo actual (tanto en el eje x como en el y) para superar la distancia comprendida por el lado de uno de los rectangulos de la cuadricula del mapa 2D (osease CELL_WIDHT y CELL_HEIGHT para cada uno de sus relativos ejes)
//c->map_edge_x y c->map_edge_y son los bordes de la cuadricula más cercanos a la posicion actual del jugador
void	delta_distance(t_cub *c)
{
	c->map_edge_x = (int)floor(c->p_x / CELL_WIDHT) * CELL_WIDHT;
	c->map_edge_y = (int)floor(c->p_y / CELL_HEIGHT) * CELL_HEIGHT;
	c->delta_dist_x = fabs(1 / c->ray_dx);
	c->delta_dist_y = fabs(1 / c->ray_dy);
	
/* 	printf("DELTA_DISTANCE\n");
	printf("c->map_edge_x = (int)(c->p_x) \n%d = (int)%lf\n", c->map_edge_x, (c->p_x));
	printf("c->map_edge_y = (int)(c->p_y) \n%d = (int)%lf\n", c->map_edge_y, (c->p_y));
	printf("c->delta_dist_x = fabs(1 / c->ray_dx) \n%lf = %lf\n", c->delta_dist_x, c->ray_dx);
	printf("c->delta_dist_y = fabs(1 / c->ray_dy) \n%lf = %lf\n", c->delta_dist_y, c->ray_dy);
	printf("\n"); */
}

//step_x y step_y indican el sentido en el que el rayo debe avanzar en la cuadrícula del mapa (hacia la izquierda o derecha en el eje x y hacia arriba o abajo en el eje y). Cada uno solo puede ser 1 o -1.
//c->side_dist_x y c->side_dist_y son la distancia absoluta hasta el siguiente rectangulo si el jugador mantiene el rumbo actual. (c->p_x - c->map_edge_x) es la distancia más corta posible hasta el siguiente rectangulo del mapa (es perpendicular al eje al que queremos llegar). Esa distancia inicial se multiplica por c->delta_dist_x, para tener en cuenta que podemos no estar yendo en la dirección ideal

void	initial_distance(t_cub *c)
{	
	if (c->ray_dx < 0)
	{
		c->step_x = -1;
		c->side_dist_x = (c->p_x - c->map_edge_x) * c->delta_dist_x;
	}
	else
	{
		c->step_x = 1;
		c->side_dist_x = (c->map_edge_x + CELL_WIDHT - c->p_x) * c->delta_dist_x;
	}
	if (c->ray_dy < 0)
	{
		c->step_y = -1;
		c->side_dist_y = (c->p_y - c->map_edge_y) * c->delta_dist_y;
	}
	else
	{
		c->step_y = 1;
		c->side_dist_y = (c->map_edge_y + CELL_HEIGHT - c->p_y) * c->delta_dist_y;
	}
	
	/* printf("INITIAL_DISTANCE\n");
	printf("c->step_x = %d\n", c->step_x);
	printf("c->side_dist_x = (c->p_x - c->map_edge_x) * c->delta_dist_x \n%lf = (%lf - %d) * %lf\n", c->side_dist_x, c->p_x, c->map_edge_x, c->delta_dist_x);
	printf("c->step_y = %d\n", c->step_y);
	printf("c->side_dist_y = (c->p_y - c->map_edge_y) * c->delta_dist_y \n%lf = (%lf - %d) * %lf\n", c->side_dist_y, c->p_y, c->map_edge_y, c->delta_dist_y); */
}

//El rayo avanza hasta encontrar una pared. Con cada avance se determina si el siguiente eje en cruzarse con el rayo será horizontal o vertical
//Despues le suma c->delta_dist_x * CELL_WIDHT, lo que le cuesta cruzar un rectangulo si empieza en el filo
//Determina la posición del jugador c->map_edge_x += c->step_x * CELL_WIDHT; sumandoles a sus coordenadas una casilla en la dirección adecuada
//Para luego if (c->map[c->map_edge_x][c->map_edge_y] == '1') com probar si ha llegado a una pared 
//c->side es un interruptor

void	digital_differential_analysis(t_cub *c)
{
	while (42)
	{
		printf("DIGITAL_DIFFERENTIAL_ANALYSIS\n");

/* 		printf("c->side_dist_x %lf c->side_dist_y %lf \nc->delta_dist_x %lf c->delta_dist_y %lf\n", c->side_dist_x, c->side_dist_y, c->delta_dist_x, c->delta_dist_y);
		printf("c->map_edge_x %d c->map_edge_y %d \n", c->map_edge_x, c->map_edge_y); */

		if (c->side_dist_x < c->side_dist_y)
		{
			c->side_dist_x += c->delta_dist_x * CELL_WIDHT;
			c->map_edge_x += c->step_x * CELL_WIDHT;
			c->side = 0;
		}
		else
		{
			c->side_dist_y += c->delta_dist_y * CELL_HEIGHT;
			c->map_edge_y += c->step_y * CELL_HEIGHT;
			c->side = 1;
		}	
		
		if (c->map[c->map_edge_y / CELL_WIDHT][c->map_edge_x / CELL_HEIGHT] == '1')
			break;
	}

	printf("c->side_dist_x %lf c->side_dist_y %lf \nc->delta_dist_x %lf c->delta_dist_y %lf \n", c->side_dist_x, c->side_dist_y, c->delta_dist_x, c->delta_dist_y);
	printf("c->map_edge_x %d c->map_edge_y %d \n", c->map_edge_x, c->map_edge_y);
}

void	wall_distance(t_cub *c)
{
/* 	printf("WALL_DISTANCE\n"); */

	if (c->side == 0)
		c->wall_dist = (c->map_edge_x - c->p_x + (1 - c->step_x) / 2) / c->ray_dx;
	else
		c->wall_dist = (c->map_edge_y - c->p_y + (1 - c->step_y) / 2) / c->ray_dy;
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

/* 	printf("c->wall_height = %lf\n\n", c->wall_height); */
}
