/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:40:41 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/21 17:01:22 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	detect_doors_aux(t_cub *c, t_ray *r, t_door *d)
{
	if ((r->was_hit_vertical && (r->rayangle > PI * 1 / 2 \
	&& r->rayangle < PI * 3 / 2) \
	&& (d->x_door == c->map_grid_index_x - 1 && \
	d->y_door == c->map_grid_index_y)) \
	|| (r->was_hit_vertical && !(r->rayangle > \
	PI * 1 / 2 && r->rayangle < PI * 3 / 2) \
	&& (d->x_door == c->map_grid_index_x && \
	d->y_door == c->map_grid_index_y)) \
	|| (!r->was_hit_vertical && ((r->rayangle < \
	PI && r->rayangle > 0)) \
	&& (d->x_door == c->map_grid_index_x && d->y_door == \
	c->map_grid_index_y)) \
	|| (!r->was_hit_vertical && !((r->rayangle < PI && \
	r->rayangle > 0)) \
	&& (d->x_door == c->map_grid_index_x && d->y_door == \
	c->map_grid_index_y - 1)))
		return (1);
	else
		return (0);
}
