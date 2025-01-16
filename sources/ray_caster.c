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
	t_ray *r;
	
	c->ray_index = 0;
	while (c->ray_index < WIN_WIDHT) //por cada uno de los 1300 bytes del juego en el eje x proyectamos un rayo
	{
		r = &c->rays[c->ray_index];
		r->relative_ray_index = (2 * c->ray_index / (double)WIN_WIDHT) - 1; //ray_camera varia entre -1 (izq del todo) y 1 (derecha del todo). Si es 0 está en el centro
		r->ray_dx = c->p_angle_x + c->camera_x * r->relative_ray_index;
		r->ray_dy = c->p_angle_y + c->camera_y * r->relative_ray_index;
		
/* 		printf("RAY_DIRECTION\n");
		printf("x = %d\n", ray_index);
		printf("r->ray_index = (2 * x / (double)WIN_WIDHT) - 1 \n%lf = (2 * %d / %lf) - 1\n", r->relative_ray_index, ray_index, (double)WIN_WIDHT - 1);
		printf("r->ray_dx = r->p_angle_x + r->camera_x * r->relative_ray_index \n%lf = %lf + %lf * %lf\n", r->ray_dx, r->p_angle_x, r->camera_x, r->relative_ray_index);
		printf("r->ray_dy = r->p_angle_y + r->camera_y * r->relative_ray_index \n%lf = %lf + %lf * %lf\n", r->ray_dy, r->p_angle_y, r->camera_y, r->relative_ray_index);
		printf("\n"); */

		delta_distance(c, r);
		initial_distance(c, r);
		digital_differential_analysis(c, r);
		wall_distance(c, r);

		draw_rays_3Dmap(c->ray_index, c, r);

		c->ray_index++;
	}
	render_3Dmap(c);
}

//fabs() valor absoluto de un punto flotante (decimal)
//c->delta_dist_x y c->delta_dist_y son la distancia relativa (relativa a CELL_WIDHT y CELL_HEIGHT) que el rayo debera recorrer con su angulo actual (tanto en el eje x como en el y) para superar la distancia comprendida por el lado de uno de los rectangulos de la cuadricula del mapa 2D (osease CELL_WIDHT y CELL_HEIGHT para cada uno de sus relativos ejes)
//c->map_edge_x y c->map_edge_y son los bordes de la cuadricula más cercanos a la posicion actual del jugador
void	delta_distance(t_cub *c, t_ray *r)
{
	r->map_edge_x = (int)floor(c->p_x / CELL_WIDHT) * CELL_WIDHT;
	r->map_edge_y = (int)floor(c->p_y / CELL_HEIGHT) * CELL_HEIGHT;
	r->delta_dist_x = fabs(1 / r->ray_dx);
	r->delta_dist_y = fabs(1 / r->ray_dy);
	
/* 	printf("DELTA_DISTANCE\n");
	printf("c->map_edge_x = (int)(c->p_x) \n%d = (int)%lf\n", c->map_edge_x, (c->p_x));
	printf("c->map_edge_y = (int)(c->p_y) \n%d = (int)%lf\n", c->map_edge_y, (c->p_y));
	printf("c->delta_dist_x = fabs(1 / c->ray_dx) \n%lf = %lf\n", c->delta_dist_x, c->ray_dx);
	printf("c->delta_dist_y = fabs(1 / c->ray_dy) \n%lf = %lf\n", c->delta_dist_y, c->ray_dy);
	printf("\n"); */
}

//step_x y step_y indican el sentido en el que el rayo debe avanzar en la cuadrícula del mapa (hacia la izquierda o derecha en el eje x y hacia arriba o abajo en el eje y). Cada uno solo puede ser 1 o -1.
//c->side_dist_x y c->side_dist_y son la distancia absoluta hasta el siguiente rectangulo si el jugador mantiene el rumbo actual. (c->p_x - c->map_edge_x) es la distancia más corta posible hasta el siguiente rectangulo del mapa (es perpendicular al eje al que queremos llegar). Esa distancia inicial se multiplica por c->delta_dist_x, para tener en cuenta que podemos no estar yendo en la dirección ideal

void	initial_distance(t_cub *c, t_ray *r)
{	
	
	
	
	if (r->ray_dx < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (c->p_x - r->map_edge_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_edge_x + CELL_WIDHT - c->p_x) * r->delta_dist_x;
	}
	if (r->ray_dy < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (c->p_y - r->map_edge_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_edge_y + CELL_HEIGHT - c->p_y) * r->delta_dist_y;
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
//c->side es un interruptor, inidica contra que eje del cuadrado va a chocar el rayo, si el x o el y

void	digital_differential_analysis(t_cub *c, t_ray *r)
{
	while (42)
	{
/* 		printf("DIGITAL_DIFFERENTIAL_ANALYSIS\n");

		printf("c->side_dist_x %lf c->side_dist_y %lf \nc->delta_dist_x %lf c->delta_dist_y %lf\n", c->side_dist_x, c->side_dist_y, c->delta_dist_x, c->delta_dist_y);
		printf("c->p_x %lf c->p_y %lf \n", c->p_x, c->p_y);
		printf("c->map_edge_x %d c->map_edge_y %d \n", c->map_edge_x, c->map_edge_y); */

		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x * CELL_WIDHT;
			r->map_edge_x += r->step_x * CELL_WIDHT;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y * CELL_HEIGHT;
			r->map_edge_y += r->step_y * CELL_HEIGHT;
			r->side = 1;
		}	
		if (c->map[r->map_edge_y / CELL_WIDHT][r->map_edge_x / CELL_HEIGHT] == '1')
			break;
	}

/* 	printf("c->side_dist_x %lf c->side_dist_y %lf \nc->delta_dist_x %lf c->delta_dist_y %lf \n", c->side_dist_x, c->side_dist_y, c->delta_dist_x, c->delta_dist_y);
	printf("c->map_edge_x %d c->map_edge_y %d \n", c->map_edge_x, c->map_edge_y); */
}

//c->wall_dist: la ditancia a la pared mas cercana. La pared (c->map_edge_x) - la posicion del jugador (c->p_x)
// + el ajuste por la desviacion del rayo que soliamos calcular con: * c->delta_dist_x = fabs(1 / c->ray_dx). 
// Ahora lo calculamos como (CELL_WIDHT * (1 - c->step_x)) / 2) / c->ray_dx, que viene a ser (CELL_WIDHT * (1 - c->step_x)) * (1 / c->ray_dx).
// (1 - c->step_x) es un interruptor. si va a la izq c->step_x es -1, con lo que CELL_WIDHT * (1 - c->step_x)) / 2 es -CELL_WIDHT. Si va a la derecha es c->step_x es 1, con lo que CELL_WIDHT * (1 - c->step_x)) / 2 es 0. y el angulo no se tiene en cuenta. 
// Esto ultimo no termino de entenderlo
// c->line_height: cuanto mas lejos este la linea mas pequeña la calcularemos
// empezaremos a dibujarla en c->draw_start = (int)(-c->line_height / 2 + WIN_HEIGHT / 2), que viene a ser (WIN_HEIGHT - c->line_height) / 2. El trozo de ventana que no vamos a dibujar es WIN_HEIGHT - c->line_height. Lo dividimos entre 2 para que la pared que vamos a dibujar este centrada sobre el eje y. Tiene tanto espacio vacio abajo como arriba. 
// c->draw_end viene a ser lo mismo que c->draw_start. Calculamos el espacio encima de la pared.

void	wall_distance(t_cub *c, t_ray *r)
{
/* 	printf("WALL_DISTANCE\n"); */

	if (r->side == 0) //pared mas cercana en el eje x
		r->wall_dist = (r->map_edge_x - c->p_x + (CELL_WIDHT * (1 - r->step_x)) / 2) / r->ray_dx;
	else //pared mas cercana en el eje y
		r->wall_dist = (r->map_edge_y - c->p_y + (CELL_HEIGHT * (1 - r->step_y)) / 2) / r->ray_dy;
	/* printf("c->wall_dist = %lf\n", c->wall_dist); */

	r->line_height = (int)(WIN_HEIGHT / r->wall_dist);
	/* printf("c->line_height = %d\n", c->line_height); */

	r->draw_start = (int)(-r->line_height / 2 + WIN_HEIGHT / 2);
	if (r->draw_start < 0)
		r->draw_start = 0;
	/* printf("c->draw_start = %d\n", c->draw_start); */

	r->draw_end = (int)(r->line_height / 2 + WIN_HEIGHT / 2);
	if (r->draw_end >= WIN_HEIGHT)
		r->draw_end = WIN_HEIGHT - 1 * CELL_HEIGHT; //DUDA: aqui no estoy tan seguro de que sea * CELL_HEIGHT
	/* printf("c->draw_end = %d\n", c->draw_end); */

/* 	if (c->side == 0) //pared mas cercana en el eje x
		c->wall_height = c->p_y + c->wall_dist * c->ray_dx; //DUDA: que es c->wall_height??
	else
		c->wall_height = c->p_x + c->wall_dist * c->ray_dy;
	c->wall_height -= floor(c->wall_height); */
	/* printf("c->wall_height = %lf\n\n", c->wall_height); */
}

void	draw_rays_3Dmap(int x, t_cub *c, t_ray *r)
{
	int	y;
	
	y = 0;
	rays_adjustment_3Dmap(r);
	while (y < WIN_HEIGHT)
	{
		if (y < r->draw_start)
			c->map_3D[y * WIN_HEIGHT + x] = FLOOR;
		else if (r->draw_start <= y && y <= r->draw_end)
			c->map_3D[y * WIN_HEIGHT + x] = WALL;
		else if (r->draw_end < y)
			c->map_3D[y * WIN_HEIGHT + x] = CEILLING;
		y++;
	}
}

void	rays_adjustment_3Dmap(t_ray *r)
{
	if (r->draw_start /= 1.5 > 0)
		r->draw_start /= 1.5;
	if (r->draw_end *= 1.5 < WIN_HEIGHT)
		r->draw_end *= 1.5;
}

