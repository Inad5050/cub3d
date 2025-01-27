/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:02:08 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/27 15:02:17 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	load_sprite(t_texture *text, int x, int y)
{
	mlx_texture_t	*png_image;

	png_image = mlx_load_png(text->file);
	if (!png_image)
		return (0);
	text->height = png_image->height;
	text->width2 = png_image->width;
	text->img = (unsigned int **)malloc(text->height * sizeof(unsigned int *));
	if (!text->img)
		return (mlx_delete_texture(png_image), 0);
	y = -1;
	while (++y < text->height)
	{
		text->img[y] = malloc(text->width2 * sizeof(unsigned int));
		if (!text->img[y])
			return (free_sprite(text), mlx_delete_texture(png_image), 0);
		x = -1;
		while (++x < text->width2)
			text->img[y][x] = get_color(&png_image->pixels[(y * png_image->width
						+ x) * png_image->bytes_per_pixel]);
	}
	mlx_delete_texture(png_image);
	return (1);
}