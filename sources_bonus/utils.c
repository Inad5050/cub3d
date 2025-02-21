/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:42:54 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/21 12:01:44 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

float	normalize_angle(float angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle = angle + 2 * PI;
	return (angle);
}

uint32_t	get_color(uint8_t *ptr)
{
	uint32_t	b;
	uint32_t	g;
	uint32_t	r;
	uint32_t	a;

	r = (uint32_t) * (ptr);
	g = (uint32_t) * (ptr + 1);
	b = (uint32_t) * (ptr + 2);
	a = (uint32_t) * (ptr + 3);
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

uint32_t	get_color_alt(int *ptr)
{
	uint32_t	b;
	uint32_t	g;
	uint32_t	r;
	uint32_t	a;

	r = (uint32_t)ptr[0];
	g = (uint32_t)ptr[1];
	b = (uint32_t)ptr[2];
	a = (uint32_t)255;
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
