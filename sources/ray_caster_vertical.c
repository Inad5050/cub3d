/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_vertical.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:20:20 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/22 18:21:04 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* void	find_vertical_hit(t_cub *c, t_ray	*r, float rayAngle, int stripid)
{	
	rayAngle = normalizeAngle(rayAngle);
	
	r->isRayFacingDown = (rayAngle > 0 && rayAngle < PI);
	r->isRayFacingUp = !r->isRayFacingDown;
	r->isRayFacingRight = (rayAngle < 0.5 * PI) || (rayAngle > 1.5 * PI);
	r->isRayFacingLeft = !r->isRayFacingRight;

	r->foundVerticalWallHit = FALSE;
	r->verticalWallHitX = 0;
	r->verticalWallHitY = 0;
	r->verticalWallContent = 0;

	find_vertical_hit_aux(c, r, rayAngle, stripid);
} */

void	find_vertical_hit(t_cub *c, t_ray *r, float rayAngle, int stripid)
{
	r->xintercept = floor(c->p_x / TILE_SIZE) * TILE_SIZE;
	if (r->isRayFacingRight)
		r->yintercept += TILE_SIZE;
	r->yintercept = c->p_y + (r->xintercept - c->p_x) / tan(rayAngle);
	r->xstep = TILE_SIZE;
	if (r->isRayFacingLeft)
		r->ystep *= -1;
	r->ystep = TILE_SIZE / tan(rayAngle);
	if (r->isRayFacingUp && r->xstep > 0)
		r->ystep *= -1;
	if (r->isRayFacingDown && r->xstep < 0)
		r->ystep *= -1;
	find_vertical_hit_loop(c, r, rayAngle, stripid);
}

void	find_vertical_hit_loop(t_cub *c, t_ray *r, float rayAngle, int stripid)
{
	r->nextHorzTouchX = r->xintercept;
	r->nextHorzTouchY = r->yintercept;
	while(r->nextHorzTouchX >= 0 && r->nextHorzTouchX <= WIN_WIDHT \
	&& r->nextHorzTouchY >= 0 && r->nextHorzTouchY <= WIN_HEIGHT)
	{
		r->xToCheck = r->nextHorzTouchX;
		if (r->isRayFacingLeft)
			r->xToCheck - 1;
		r->yToCheck = r->nextHorzTouchY;
		if (mapHasWallAt(c, r->xToCheck, r->yToCheck)) 
		{
			r->verticalWallHitX = r->nextHorzTouchX; 
			r->verticalWallHitY = r->nextHorzTouchY;
			r->verticalWallContent = c->map[(int)floor(r->yToCheck / TILE_SIZE)][(int)floor(r->xToCheck / TILE_SIZE)];	
			r->foundVerticalWallHit = TRUE;
			break;		
		}
		else
		{
			r->nextHorzTouchX += r->xstep;
			r->nextHorzTouchY += r->ystep;
		}
	}
}
