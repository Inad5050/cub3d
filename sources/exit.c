/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:30:49 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/09 12:04:28 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	c_error(char *str, t_cub *c)
{
	ft_printf("%s\n", str);
	mlx_destroy_window(c->mlx, c->win_mlx);	
	free_memory(c);
	exit (EXIT_FAILURE);
}

int	c_close(t_cub *c)
{
	mlx_destroy_window(c->mlx, c->win_mlx);	
	free_memory(c);
	return (exit (EXIT_FAILURE), 0);
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