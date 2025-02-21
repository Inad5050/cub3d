/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:52:48 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/21 17:56:18 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	ray_caster(t_cub *c)
{
	float	rayangle;
	int		ray_index;
	t_ray	*r;

	rayangle = c->p_rotationangle - (c->p_fov / 2);
	ray_index = 0;
	while (ray_index < NUM_RAYS)
	{
		r = &(c->rays[ray_index]);
		cast_ray(c, r, ray_index, rayangle);
		rayangle = r->rayangle + c->p_fov / NUM_RAYS;
		ray_index++;
	}
}

void	cast_ray(t_cub *c, t_ray *r, int ray_index, float rayangle)
{
	init_ray_struct(r, ray_index, rayangle);
	find_horizontal_hit(c, r, rayangle);
	find_vertical_hit(c, r, rayangle);
	select_ray_hit(c, r);
	detect_doors(c, r);
}

void	init_ray_struct(t_ray *r, int ray_index, float rayangle)
{
	ft_memset(r, 0, sizeof(t_ray));
	rayangle = normalize_angle(rayangle);
	r->rayangle = rayangle;
	r->ray_index = ray_index;
	r->israyfacingdown = (rayangle > 0 && rayangle < PI);
	r->israyfacingup = !r->israyfacingdown;
	r->israyfacingright = (rayangle < 0.5 * PI) || (rayangle > 1.5 * PI);
	r->israyfacingleft = !r->israyfacingright;
}

void	select_ray_hit(t_cub *c, t_ray *r)
{
	if (r->found_horizontal_wall_hit)
		r->horizontal_hit_distance = distance_between_points(c->p_x, c->p_y, \
		r->horizontal_wall_hit_x, r->horizontal_wall_hit_y);
	else
		r->horizontal_hit_distance = INT_MAX;
	if (r->found_vertical_wall_hit)
		r->vertical_hit_distance = distance_between_points(c->p_x, c->p_y, \
		r->vertical_wall_hit_x, r->vertical_wall_hit_y);
	else
		r->vertical_hit_distance = INT_MAX;
	if (r->vertical_hit_distance < r->horizontal_hit_distance)
	{
		r->distance = r->vertical_hit_distance;
		r->wall_hit_x = r->vertical_wall_hit_x;
		r->wall_hit_y = r->vertical_wall_hit_y;
		r->was_hit_vertical = TRUE;
	}
	else
	{
		r->distance = r->horizontal_hit_distance;
		r->wall_hit_x = r->horizontal_wall_hit_x;
		r->wall_hit_y = r->horizontal_wall_hit_y;
		r->was_hit_vertical = FALSE;
	}
}
