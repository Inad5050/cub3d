/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:52:48 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/22 20:18:32 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ray_caster(t_cub *c) //inicializa el algoritmo para cada uno de los rayos
{
	float	rayAngle;
	int		stripid;

	stripid = 0;
	rayAngle = c->p_rotationangle - (c->player_fov / 2); //inicializa el angulo del primer rayo como el angulo del jugador - la mitad del FOV
	while (stripid < NUM_RAYS)
	{
		if (cast_ray(c, rayAngle, stripid) != 0) //funcion para manjar los rayos
			break ;
		rayAngle += c->player_fov / NUM_RAYS; //incrementamos el angulo del siguiente rayo la parte proporcional que le corresponde del total del angulo del FOV (si nuestro FOV es de 60 grados y tenemos 2000 rayos lo incrementamos en 60/2000)
		stripid++;
	}
}

//rayangle: angulo del siguiente rayo que vamos a castear. Su valor se inicializa como el valor del angulo del jugador (player.rotationangle) - la mitad del FOV (porque el FOV está centrado en el angulo del jugador y debe ser igual a cada lado). Lo aumentamos en la parte proporcional que le corresponde cada vez que pasamos al siguiente rayo. 
//stripid: indice de cada rayo
//player.rotationangle: se inicializa como PI/2 = 90 grados = horientacion norte
//game->player.fov: el angulo de vision del jugador. Se inicializa como (60 * PI / 180). Hasta donde entiendo su valor no cambia durante la ejecucion del programa
//NUM_RAYS = WIN_WIDHT = 2000
//game: estructura

int	cast_ray(t_cub *c, float rayAngle, int stripid)
{
	t_ray	*r;

	r = &c->rays[stripid];
	
	init_ray_struct(r, rayAngle);
	find_horizontal_hit(c, r, rayAngle);
	find_vertical_hit(c, r, rayAngle);
	choose_hit(c, r, rayAngle);
	
	//...

	return (0);
}

void	init_ray_struct(t_ray *r, float rayAngle)
{
	rayAngle = normalizeAngle(rayAngle); //hace que el angulo sea positivo y menor a 360 grados

	ft_memset(r, 0, sizeof(t_ray));
		
	r->isRayFacingDown = (rayAngle > 0 && rayAngle < PI); //si el angulo es positivo (depende unicamente de la rotacion, para ser positivo debe ser rotacion antihoraria) && y el angulo es menor a 180 (PI) grados
	r->isRayFacingUp = !r->isRayFacingDown;
	r->isRayFacingRight = (rayAngle < 0.5 * PI) || (rayAngle > 1.5 * PI);
	r->isRayFacingLeft = !r->isRayFacingRight;

//esta parte deberia ser sustituida por memset
/* 	r->horizontalWallHitX = 0;
	r->horizontalWallHitY = 0;
	r->horizontalWallContent = 0;
	r->foundHorizontalWallHit = FALSE;
	
	r->verticalWallHitX = 0;
	r->verticalWallHitY = 0;
	r->verticalWallContent = 0;
	r->foundVerticalWallHit = FALSE; */
}

void	choose_hit(t_cub *c, t_ray *r, float rayAngle)
{
	if (r->foundHorizontalWallHit)
		r->horizontalHitDistance = distanceBetweenPoints(c->p_x, c->p_y, r->horizontalWallHitX, r->horizontalWallHitY);
	else  
		r->horizontalHitDistance = INT_MAX;
	if (r->foundVerticalWallHit)
		r->verticalHitDistance = distanceBetweenPoints(c->p_x, c->p_y, r->verticalWallHitX, r->verticalWallHitY);
	else  
		r->verticalHitDistance = INT_MAX;
	if (r->verticalHitDistance < r->horizontalHitDistance)
	{
		r->distance = r->verticalHitDistance;
		r->wallHitX = r->verticalWallHitX;
		r->wallHitY = r->verticalWallHitY;
		r->wallHitContent = r->verticalWallContent;
		r->wasHitVertical = TRUE;		
	}
	else
	{
		r->distance = r->horizontalHitDistance;
		r->wallHitX = r->horizontalWallHitX;
		r->wallHitY = r->horizontalWallHitY;
		r->wallHitContent = r->horizontalWallContent;
		r->wasHitVertical = FALSE;		
	}	
}
