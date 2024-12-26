/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:21:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/12/26 18:02:53 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	free_memory(t_cub *c) //libera toda la memoria
{
	mlx_close_window(c->mlx); //funcion de MLX, cierra la ventana
	mlx_terminate(c->mlx); //funcion de MLX, libera la memoria de MLX
	
	//...
	
	free_img(c);
	if (c)
		free(c);
}

void	free_img(t_cub *c) //destruye la textura y libera el nombre+ruta de la imagen. MLX terminate no se encarga de esto?
{
	if (c->texture_floor)
		mlx_delete_texture(c->texture_floor);
	if (c->png_floor)
		free(c->png_floor);
	if (c->texture_wall)
		mlx_delete_texture(c->texture_wall);
	if (c->png_wall)
		free(c->png_wall);

	//...

}
