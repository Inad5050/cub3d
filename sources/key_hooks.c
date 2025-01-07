/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:44:08 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/07 20:09:55 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	key_hooks(int keysym, t_cub *c)
{	
	if (keysym == KEY_ESC)
		c_close(c);
	else if ((keysym == KEY_W || keysym == KEY_UP) && !(is_in_wall(-1, 0, c)))
		c->p->p_y -= STEP_SIZE;
	else if ((keysym == KEY_S || keysym == KEY_DOWN) && !(is_in_wall(1, 0, c)))
		c->p->p_y += STEP_SIZE;
	else if ((keysym == KEY_A || keysym == KEY_LEFT) && !(is_in_wall(0, -1, c)))
		c->p->p_x -= STEP_SIZE;
	else if ((keysym == KEY_D || keysym == KEY_RIGHT) && !(is_in_wall(0, 1, c)))
		c->p->p_x += STEP_SIZE;
	map_render(c);
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
		tmp_p_y = (int)floor(c->p->p_y + (double)(STEP_SIZE * y)) / IMG_HEIGHT;
		tmp_p_x = floor(c->p->p_x) / IMG_WIDHT;
		if (c->map[tmp_p_y][tmp_p_x] != '0')		
			return (printf("return = 1\n"), 1);
	}
	if (x)
	{
		tmp_p_y = floor(c->p->p_y) / IMG_HEIGHT;
		tmp_p_x = (int)floor(c->p->p_x + (double)(STEP_SIZE * x)) / IMG_WIDHT;
		if (c->map[tmp_p_y][tmp_p_x] != '0')	
			return (printf("return = 1\n"), 1);
	}
	return (printf("return = 0\n"), 0);	
}
