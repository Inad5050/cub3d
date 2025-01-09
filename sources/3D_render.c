/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:04:02 by dani              #+#    #+#             */
/*   Updated: 2025/01/09 12:31:53 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	create_img_buffer(t_cub *c)
{
	create_img_buffer_aux(c->ceiling, c);
	create_img_buffer_aux(c->ceiling, c);
	create_img_buffer_aux(c->ceiling, c);
	create_img_buffer_aux(c->ceiling, c);
	create_img_buffer_aux(c->ceiling, c);
	create_img_buffer_aux(c->ceiling, c);
}

void	create_img_buffer_aux(t_img *m, t_cub *c)
{
	m->buffer = ft_strdup((char *)m->addr);
	if (!m->buffer)
		c_error("Cannot alloc in create_img_buffer_aux", c);	
}

void	print_pixel_map(t_cub *c)
{
	









}