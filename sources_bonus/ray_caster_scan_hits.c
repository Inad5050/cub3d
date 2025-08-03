/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_scan_hits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:19:39 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/21 16:34:24 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	find_horizontal_hit(t_cub *c, t_ray *r, float rayAngle)
{
	r->found_horizontal_wall_hit = 0;
	r->horizontal_wall_hit_x = 0;
	r->horizontal_wall_hit_y = 0;
	r->horizontal_wall_content = 0;
	r->yintercept = floor(c->p_y / TILE_SIZE) * TILE_SIZE;
	if (r->israyfacingdown)
		r->yintercept += TILE_SIZE;
	r->xintercept = c->p_x + (r->yintercept - c->p_y) / tan(rayAngle);
	r->ystep = TILE_SIZE;
	if (r->israyfacingup)
		r->ystep *= -1;
	r->xstep = TILE_SIZE / tan(rayAngle);
	if (r->israyfacingleft && r->xstep > 0)
		r->xstep *= -1;
	if (r->israyfacingright && r->xstep < 0)
		r->xstep *= -1;
	find_horizontal_hit_loop(c, r);
}

void	find_horizontal_hit_loop(t_cub *c, t_ray *r)
{
	r->next_horz_touch_x = r->xintercept;
	r->next_horz_touch_y = r->yintercept;
	while (r->next_horz_touch_x >= 0 && r->next_horz_touch_x <= c->map_max_x \
	&& r->next_horz_touch_y >= 0 && r->next_horz_touch_y <= c->map_max_y)
	{
		r->x_to_check = r->next_horz_touch_x;
		r->y_to_check = r->next_horz_touch_y;
		if (r->israyfacingup)
			r->y_to_check -= 1;
		if (has_wall_at(c, r->x_to_check, r->y_to_check) == 1)
		{
			r->horizontal_wall_hit_x = r->next_horz_touch_x;
			r->horizontal_wall_hit_y = r->next_horz_touch_y;
			r->found_horizontal_wall_hit = TRUE;
			break ;
		}
		r->next_horz_touch_x += r->xstep;
		r->next_horz_touch_y += r->ystep;
	}
}

void	find_vertical_hit(t_cub *c, t_ray *r, float rayAngle)
{
	r->found_vertical_wall_hit = 0;
	r->vertical_wall_hit_x = 0;
	r->vertical_wall_hit_y = 0;
	r->vertical_wall_content = 0;
	r->xintercept = floor(c->p_x / TILE_SIZE) * TILE_SIZE;
	if (r->israyfacingright)
		r->xintercept += TILE_SIZE;
	r->yintercept = c->p_y + (r->xintercept - c->p_x) * tan(rayAngle);
	r->xstep = TILE_SIZE;
	if (r->israyfacingleft)
		r->xstep *= -1;
	r->ystep = TILE_SIZE * tan(rayAngle);
	if (r->israyfacingup && r->ystep > 0)
		r->ystep *= -1;
	else if (r->israyfacingdown && r->ystep < 0)
		r->ystep *= -1;
	find_vertical_hit_loop(c, r);
}

void	find_vertical_hit_loop(t_cub *c, t_ray *r)
{
	r->next_vertical_touch_x = r->xintercept;
	r->next_vertical_touch_y = r->yintercept;
	while (r->next_vertical_touch_x >= 0 && r->next_vertical_touch_x \
	<= c->map_max_x && r->next_vertical_touch_y >= 0 && \
	r->next_vertical_touch_y <= c->map_max_y)
	{
		r->x_to_check = r->next_vertical_touch_x;
		if (r->israyfacingleft)
			r->x_to_check -= 1;
		r->y_to_check = r->next_vertical_touch_y;
		if (has_wall_at(c, r->x_to_check, r->y_to_check) == 1)
		{
			r->vertical_wall_hit_x = r->next_vertical_touch_x;
			r->vertical_wall_hit_y = r->next_vertical_touch_y;
			r->found_vertical_wall_hit = TRUE;
			break ;
		}
		r->next_vertical_touch_x += r->xstep;
		r->next_vertical_touch_y += r->ystep;
	}
}

int	has_wall_at(t_cub *c, float x, float y)
{
	int		map_grid_index_x;
	int		map_grid_index_y;
	char	tile;

	map_grid_index_x = ((int)x / TILE_SIZE);
	map_grid_index_y = ((int)y / TILE_SIZE);
	if (map_grid_index_y < 0 || map_grid_index_y >= c->map_max_y)
		return (0);
	if (map_grid_index_x < 0 || \
	map_grid_index_x >= (int)ft_strlen(c->map[map_grid_index_y]))
		return (0);
	tile = c->map[map_grid_index_y][map_grid_index_x];
	if (tile == 'M')
		return (2);
	if (tile == '1')
		return (1);
	return (0);
}
