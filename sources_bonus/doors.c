/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:13:00 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/07 20:52:12 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	init_doors(t_cub *c)
{	
	if (!c->door_number)
		return ;
	c->doors = ft_calloc(c->door_number, sizeof(t_door));
	if (!c->doors)
		c_error("Couldn't alloc in init_doors", c);
	locate_doors(c);
}

void	locate_doors(t_cub *c)
{
	int	y;
	int	x;
	int	door_index;

	door_index = 0;
	y = 0;
	while(c->map[y])
	{
		x = 0;
		while(c->map[y][x])
		{
			if (c->map[y][x] == 'D' && door_index < c->door_number)
			{
				c->map[y][x] = '1';
				c->doors[door_index].x_door = x;
				c->doors[door_index].y_door = y;
				c->doors[door_index].is_closed = TRUE;
				door_index++;
			}
			x++;
		}
		y++;		
	}	
}

void	open_doors(t_cub *c)
{
	int		door_index;
	float	distance;
	t_door	*d;
	
	if (!c->door_number || !mlx_is_key_down(c->mlx, MLX_KEY_SPACE))
		return ;
	door_index = 0;
	while (door_index < c->door_number)
	{
		d = &c->doors[door_index];
		distance = distance_between_points(c->p_x, c->p_y, 
		d->x_door * TILE_SIZE, d->y_door * TILE_SIZE);
		if (distance <= OPEN_DISTANCE && d->is_closed && !d->opening)
			d->opening = 1;
/* 		if (distance <= OPEN_DISTANCE && !d->is_closed && !d->opening && c->map[d->y_door][d->x_door] == 0)
			d->closing = 1; */
		door_index++;
	}
}

void	detect_doors(t_cub *c, t_ray *r)
{
	int		door_index;
	t_door	*d;
	int		map_grid_index_x;
	int		map_grid_index_y;
	
	if (!c->door_number)
		return ;	
	door_index = 0;
	map_grid_index_x = ((int)r->wall_hit_x / TILE_SIZE); //cuando casteamos un float a int perdemos los valores decimales, redondeando el valor de las coordenadas al borde de la casilla actual
	map_grid_index_y = ((int)r->wall_hit_y / TILE_SIZE);
	while (door_index < c->door_number)
	{
		d = &c->doors[door_index];

		/* printf("d->x_door %d map_grid_index_x - 1 %d d->y_door %d map_grid_index_y %d\n", d->x_door, map_grid_index_x - 1, d->y_door, map_grid_index_y); */
		
		if (d->x_door == map_grid_index_x - 1 && d->y_door == map_grid_index_y)
		{
			/* printf("d->x_door %d map_grid_index_x - 1 %d d->y_door %d map_grid_index_y %d\n", d->x_door, map_grid_index_x - 1, d->y_door, map_grid_index_y); */
			r->im_door = 1;
			r->im_door_number = door_index;
		}
		door_index++;
	}
}

void	update_doors(t_cub *c)
{
	int		door_index;
	t_door	*d;

	door_index = 0;
	while (door_index < c->door_number)
	{
		d = &c->doors[door_index];
		if(d->opening)
			d->opening++;
		if (d->opening >= OPEN_TIME)
		{
			d->opening = 0;
			d->is_closed = FALSE;
			c->map[d->y_door][d->x_door] = '0';
		}
		door_index++;
	}
}
