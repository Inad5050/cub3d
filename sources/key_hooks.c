/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:44:08 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/15 13:03:06 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	key_hooks(int keysym, t_cub *c)
{	
	if (keysym == KEY_ESC)
		c_close(c);
	else if ((keysym == KEY_W) && !(is_in_wall(-1, 0, c)))
		c->p_y -= STEP_SIZE;
	else if ((keysym == KEY_S) && !(is_in_wall(1, 0, c)))
		c->p_y += STEP_SIZE;
	else if ((keysym == KEY_A) && !(is_in_wall(0, -1, c)))
		c->p_x -= STEP_SIZE;
	else if ((keysym == KEY_D) && !(is_in_wall(0, 1, c)))
		c->p_x += STEP_SIZE;
	else if ((keysym == KEY_LEFT))
		rotate_player(0, c);
	else if ((keysym == KEY_RIGHT))
		rotate_player(1, c);
	map_render(c);
	ray_direction(c);
	return (0);
}

int	is_in_wall(int y, int x, t_cub *c)
{
	int	tmp_p_y;
	int	tmp_p_x;
	
	tmp_p_y = 0;
	tmp_p_x = 0;
	if (y)
	{
		tmp_p_y = (int)floor(c->p_y + (double)(STEP_SIZE * y)) / CELL_HEIGHT;
		tmp_p_x = (int)floor(c->p_x) / CELL_WIDHT;
		if (c->map[tmp_p_y][tmp_p_x] != '0')		
			return (1);
	}
	else if (x)
	{
		tmp_p_y = (int)floor(c->p_y) / CELL_HEIGHT;
		tmp_p_x = (int)floor(c->p_x + (double)(STEP_SIZE * x)) / CELL_WIDHT;
		if (c->map[tmp_p_y][tmp_p_x] != '0')	
			return (1);
	}
	return (0);	
}

void	rotate_player(int right_dir, t_cub *c)
{
	if (!right_dir)
	{
		c->p_angle -= 0.1;
		if (c->p_angle < 0)
			c->p_angle += 2*PI; //en C los valores de un angulo van de 0 a 2PI, si sobrepasamos el 0 volvemos a empezar por 0/2PI
	}
	if (right_dir)
	{
		c->p_angle += 0.1;
		if (c->p_angle > 2*PI)
			c->p_angle -= 2*PI; //en C los valores de un angulo van de 0 a 2PI, si sobrepasamos el 0 volvemos a empezar por 0/2PI
	}
	c->p_angle_y = sin(c->p_angle) * FIELD_OF_VIEW; //cada vez que cambia el angulo cambian los deltas de cada eje del jugador
	c->p_angle_x = cos(c->p_angle) * FIELD_OF_VIEW;
	c->camera_x = c->p_angle_y * FIELD_OF_VIEW; //cada vez que cambia el angulo cambia el angulo de la camara (es perpendicular a el eje del jugador)
	c->camera_y = c->p_angle_x * FIELD_OF_VIEW;
}

