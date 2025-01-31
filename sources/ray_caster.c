/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:52:48 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/31 16:18:35 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//FUNCIONA COMO LA DE DAVID (FCD de ahora en adelante)
void	ray_caster(t_cub *c) //inicializa el algoritmo para cada uno de los rayos
{
	float	rayAngle;
	int		ray_index;
	t_ray	*r;

	rayAngle = c->p_rotationangle - (c->p_fov / 2); //inicializa el angulo del primer rayo como el angulo del jugador - la mitad del FOV	
	ray_index = 0;
	/* printf("rayAngle = %f c->p_rotationangle = %f c->p_fov = %f\n", rayAngle, c->p_rotationangle, c->p_fov); */
	while (ray_index < NUM_RAYS)
	{
		r = &(c->rays[ray_index]);		
		cast_ray(c, r, ray_index, rayAngle); //funcion para manjar los rayos		
		rayAngle = r->rayangle + c->p_fov / NUM_RAYS; //incrementamos el angulo del siguiente rayo la parte proporcional que le corresponde del total del angulo del FOV (si nuestro FOV es de 60 grados y tenemos 2000 rayos lo incrementamos en 60/2000)
		ray_index++;
		
/* 		printf("rayAngle = %f ray_index = %d\n", rayAngle, ray_index); */
	}	
}

//rayangle: angulo del siguiente rayo que vamos a castear. Su valor se inicializa como el valor del angulo del jugador (player.rotationangle) - la mitad del FOV (porque el FOV está centrado en el angulo del jugador y debe ser igual a cada lado). Lo aumentamos en la parte proporcional que le corresponde cada vez que pasamos al siguiente rayo. 
//ray_index: indice de cada rayo
//player.rotationangle: se inicializa como PI/2 = 90 grados = horientacion norte
//game->player.fov: el angulo de vision del jugador. Se inicializa como (60 * PI / 180). Hasta donde entiendo su valor no cambia durante la ejecucion del programa
//NUM_RAYS = WIN_WIDHT = 2000
//game: estructura

void	cast_ray(t_cub *c, t_ray *r, int ray_index, float rayAngle)
{	
	init_ray_struct(r, ray_index, rayAngle);
	find_horizontal_hit(c, r, rayAngle);
	find_vertical_hit(c, r, rayAngle);	
	select_ray_hit(c, r);
}

//FCD
void	init_ray_struct(t_ray *r, int ray_index, float rayAngle) //pone a cero todos los valores de la estructura para que podamos volver a usarla. Almacena el valor del actual angulo del rayo y les da valor a las flags 
{
	ft_memset(r, 0, sizeof(t_ray));
	rayAngle = normalize_angle(rayAngle); //hace que el angulo sea positivo y menor a 360 grados
	r->rayangle = rayAngle;
	r->ray_index = ray_index;
	r->isRayFacingDown = (rayAngle > 0 && rayAngle < PI); //si el angulo es positivo (depende unicamente de la rotacion, para ser positivo debe ser rotacion antihoraria) && y el angulo es menor a 180 (PI) grados
	r->isRayFacingUp = !r->isRayFacingDown;
	r->isRayFacingRight = (rayAngle < 0.5 * PI) || (rayAngle > 1.5 * PI);
	r->isRayFacingLeft = !r->isRayFacingRight;

	/* printf("r->rayangle = %f r->ray_index = %d r->isRayFacingDown = %d r->isRayFacingUp = %d r->isRayFacingRight = %d r->isRayFacingLeft = %d\n", r->rayangle, r->ray_index, r->isRayFacingDown, r->isRayFacingUp, r->isRayFacingRight, r->isRayFacingLeft); */
	
}

void	select_ray_hit(t_cub *c, t_ray *r) //en que eje ha golpeado antes el rayo en el horizontal o en el vertical. Una vez hayamos elegido almacenamos los valores de uno o de otro
{
	if (r->foundHorizontalWallHit)
		r->horizontalHitDistance = distance_between_points(c->p_x, c->p_y, r->horizontalWallHitX, r->horizontalWallHitY);
	else  
		r->horizontalHitDistance = INT_MAX;
	if (r->foundVerticalWallHit)
		r->verticalHitDistance = distance_between_points(c->p_x, c->p_y, r->verticalWallHitX, r->verticalWallHitY);
	else  
		r->verticalHitDistance = INT_MAX;
	
/* 	printf("r->foundHorizontalWallHit = %d c->p_x = %f c->p_y = %f r->horizontalWallHitX = %f r->horizontalWallHitY = %f\n", r->foundHorizontalWallHit, c->p_x, c->p_y, r->horizontalWallHitX, r->horizontalWallHitY);
	printf("r->foundVerticalWallHit = %d c->p_x = %f c->p_y = %f r->verticalWallHitX = %f r->verticalWallHitY = %f\n", r->foundVerticalWallHit, c->p_x, c->p_y, r->verticalWallHitX, r->verticalWallHitY);
	printf("r->horizontalHitDistance = %f, r->verticalHitDistance = %f\n\n", r->horizontalHitDistance, r->verticalHitDistance);
 */	
	if (r->verticalHitDistance < r->horizontalHitDistance)
	{
		/* printf("VERTICAL\n"); */
		
		r->distance = r->verticalHitDistance;
		r->wallHitX = r->verticalWallHitX;
		r->wallHitY = r->verticalWallHitY;
		r->wallHitContent = r->verticalWallContent;
		r->wasHitVertical = TRUE;		
	}
	else
	{
		/* printf("HORIZONTAL\n"); */
		
		r->distance = r->horizontalHitDistance;
		r->wallHitX = r->horizontalWallHitX;
		r->wallHitY = r->horizontalWallHitY;
		r->wallHitContent = r->horizontalWallContent;
		r->wasHitVertical = FALSE;	
	}

	/* printf("OLA r->ray_index = %d\n", r->ray_index); */
/* 	if (r->ray_index == 0 || r->ray_index == 2)
	{
		printf("r->ray_index = %d\n", r->ray_index);
		printf("r->distance = %f\n", r->distance);
		printf("r->wallHitX = %f\n", r->wallHitX);
		printf("r->wallHitY = %f\n", r->wallHitY);
		printf("r->wallHitContent = %f\n", r->wallHitContent);
		printf("r->wasHitVertical = %f\n\n", r->wasHitVertical);
	} */
}
