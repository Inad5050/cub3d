/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:30:49 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/23 15:39:43 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	c_error(char *str, t_cub *c)
{
	ft_printf("%s\n", str);
	
	//--------------------------
	mlx_destroy_image(c->mlx, c->render->img_ptr); //si uso lo de Izaro
	//--------------------------
		
	mlx_destroy_window(c->mlx, c->win_mlx_2D);
	mlx_destroy_window(c->mlx, c->win_mlx_3D);
	free_memory(c);
	exit (EXIT_FAILURE);
}

void	c_close(t_cub *c)
{
	//--------------------------
	mlx_destroy_image(c->mlx, c->render->img_ptr); //si uso lo de Izaro
	//--------------------------
	
	mlx_destroy_window(c->mlx, c->win_mlx_2D);
	mlx_destroy_window(c->mlx, c->win_mlx_3D);	
	free_memory(c);
	exit(EXIT_SUCCESS);
}

void	free_memory(t_cub *c) //libera toda la memoria
{
	if (c->ceiling)
		free(c->ceiling);
	if (c->floor)
		free(c->floor);
	if (c->wall_n)	
		free(c->wall_n);
	if (c->wall_s)	
		free(c->wall_s);
	if (c->wall_w)	
		free(c->wall_w);
	if (c->wall_e)	
		free(c->wall_e);
	
	//...
	
	if (c)
		free(c);
}
