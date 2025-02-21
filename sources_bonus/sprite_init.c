/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:44:50 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/21 17:44:00 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	init_sprite(t_cub *c)
{
	if (!c->sprite_number)
		return ;
	c->sprites = ft_calloc(c->sprite_number, sizeof(t_sprite));
	if (!c->sprites)
		c_error("Couldn't alloc in init_sprite", c);
	locate_sprite(c);
}

void	locate_sprite(t_cub *c)
{
	int	y;
	int	x;
	int	sprite_index;

	sprite_index = 0;
	y = 0;
	while (c->map[y])
	{
		x = 0;
		while (c->map[y][x])
		{
			if (c->map[y][x] == 'S' && sprite_index < c->sprite_number)
			{
				c->map[y][x] = '0';
				c->sprites[sprite_index].x_sprite = x;
				c->sprites[sprite_index].y_sprite = y;
				sprite_index++;
			}
			x++;
		}
		y++;
	}
}

void	detect_sprites(t_cub *c, t_ray *r)
{
	int			sprite_index;
	t_sprite	*d;

	if (!c->sprite_number)
		return ;
	sprite_index = 0;
	c->map_grid_index_x = ((int)r->wall_hit_x / TILE_SIZE);
	c->map_grid_index_y = ((int)r->wall_hit_y / TILE_SIZE);
	while (sprite_index < c->sprite_number)
	{
		d = &c->sprites[sprite_index];
		if (detect_sprites_aux(c, r, d))
		{
			r->im_sprite = 1;
			r->sprite_number = sprite_index;
		}
		sprite_index++;
	}
}

int	detect_sprites_aux(t_cub *c, t_ray *r, t_sprite *d)
{
	if ((r->was_hit_vertical && (r->rayangle > PI * 1 / 2 \
	&& r->rayangle < PI * 3 / 2) \
	&& (d->x_sprite == c->map_grid_index_x - 1 && \
	d->y_sprite == c->map_grid_index_y)) \
	|| (r->was_hit_vertical && !(r->rayangle > \
	PI * 1 / 2 && r->rayangle < PI * 3 / 2) \
	&& (d->x_sprite == c->map_grid_index_x && \
	d->y_sprite == c->map_grid_index_y)) \
	|| (!r->was_hit_vertical && ((r->rayangle < \
	PI && r->rayangle > 0)) \
	&& (d->x_sprite == c->map_grid_index_x && d->y_sprite == \
	c->map_grid_index_y)) \
	|| (!r->was_hit_vertical && !((r->rayangle < PI && \
	r->rayangle > 0)) \
	&& (d->x_sprite == c->map_grid_index_x && d->y_sprite == \
	c->map_grid_index_y - 1)))
		return (1);
	else
		return (0);
}
