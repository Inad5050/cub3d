/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:21:58 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/23 13:52:29 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_image(t_cub *c)
{
	c->render = ft_calloc(sizeof(t_img), 1);
	if (!c->render)
		c_error("Cannot alocate memory for c->render in init_image\n", c);
	c->render->img_ptr = mlx_new_image(c->mlx, WIN_WIDHT, WIN_HEIGHT);
	c->render->addr = c->render->addr = mlx_get_data_addr(c->render->img_ptr, &(c->render->bpp), \
		&(c->render->line_len), &(c->render->endian));
}
