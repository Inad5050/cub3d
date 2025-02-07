/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:24:06 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/07 21:44:06 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

/* void	choose_sprite_hit(t_cub *c, t_ray *r)
{
	r->sprite_horizontal_hit_distance = distance_between_points(c->p_x, c->p_y, r->horizontal_sprite_hit_x, r->horizontal_sprite_hit_y);
	r->sprite_vertical_hit_distance = distance_between_points(c->p_x, c->p_y, r->vertical_sprite_hit_x, r->vertical_sprite_hit_y);
	if (r->sprite_horizontal_hit_distance < r->sprite_vertical_hit_distance)
	{
		r->sprite_distance = r->sprite_horizontal_hit_distance;
		r->sprite_hit_x = r->horizontal_sprite_hit_x;
		r->sprite_hit_y = r->horizontal_sprite_hit_y;
	}
	else
	{
		r->sprite_distance = r->sprite_vertical_hit_distance;
		r->sprite_hit_x = r->vertical_sprite_hit_x;
		r->sprite_hit_y = r->vertical_sprite_hit_y;
		r->sprite_was_hit_vertical = 1;
	}
} */

void	sprite_render(t_cub *c)
{
	int		index_ray;
	t_ray	*r;

	index_ray = 0;
	while (index_ray < NUM_RAYS) //por cada rayo renderizalo
	{
		r = &c->rays[index_ray];
		if (!r->is_sprite)
			return;
		if (r->sprite_distance == 0)
			r->sprite_distance = 0.1;
		r->sprite_perp_distance = r->sprite_distance * cos(r->rayangle - c->p_rotationangle);
		r->sprite_distance_proj_plane = (WIN_WIDTH / 2) / tan(c->p_fov / 2);
		r->sprite_strip_height = (TILE_SIZE / r->sprite_perp_distance) * r->sprite_distance_proj_plane;
		r->sprite_top_pixel = (WIN_HEIGHT / 2) - (r->sprite_strip_height / 2);
		r->sprite_bottom_pixel = (WIN_HEIGHT / 2) + (r->sprite_strip_height / 2);
		sprite_render_aux(c, r);
		draw_sprite_strip(c, r, index_ray);
	}
	
}

void	sprite_render_aux(t_cub *c, t_ray *r)
{
/* 	if (!r->sprite_was_hit_vertical)
	{
		if (r->rayangle < PI && r->rayangle > 0) */
			calculate_sprite_strip(c, r, c->sprite_t, TILE_SIZE - 1 - ((int)(r->sprite_hit_x + r->sprite_hit_y) % TILE_SIZE)); //muro sur, el rayo viene desde abajo
/* 		else
			calculate_sprite_strip(c, r, c->sprite_t, (int)(r->sprite_hit_x + r->sprite_hit_y) % TILE_SIZE); //muro norte
	}
	else
	{
		if (r->rayangle > PI * 1 / 2 && r->rayangle < PI * 3 / 2)
			calculate_sprite_strip(c, r, c->sprite_t, TILE_SIZE - 1 - ((int)(r->sprite_hit_x + r->sprite_hit_y) % TILE_SIZE)); //muro oeste, el rayo viene desde la derecha
		else 
			calculate_sprite_strip(c, r, c->sprite_t, (int)(r->sprite_hit_x + r->sprite_hit_y) % TILE_SIZE); //muro este
	} */
}

void	calculate_sprite_strip(t_cub *c, t_ray *r, t_texture *t, int x)
{
	int	y;
	int	anti_y;
	int	img_x;
	int	img_y;

	y =  r->sprite_top_pixel;
	img_x = 1;
	if (x != 1)
		img_x = (x * t->width) / TILE_SIZE;
	anti_y = y;
	if (r->sprite_top_pixel < 0)
		anti_y += r->sprite_top_pixel;
	while (y < r->sprite_bottom_pixel && y < WIN_HEIGHT)
	{
		img_y = ((y - anti_y) * t->height) / (r->sprite_bottom_pixel - r->sprite_top_pixel);
		if (img_y >= 0 && img_y < t->height && img_x >= 0 && img_x < t->width)
			c->sprite_strip[y] = t->pixels[img_y][img_x];
		y++;
	}
}

void	draw_sprite_strip(t_cub *c, t_ray *r, int x)
{
	int	y;

	y = r->sprite_top_pixel;
	while (++y < r->sprite_bottom_pixel)
	{
		if (c->sprite_strip[y] != WHITE_DECIMAL)
			mlx_put_pixel(c->win_mlx3D, x, y, c->sprite_strip[y]);
	}
}