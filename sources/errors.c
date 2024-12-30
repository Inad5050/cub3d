/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:30:49 by dangonz3          #+#    #+#             */
/*   Updated: 2024/12/30 21:09:04 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	c_error(char *str, t_cub *c)
{
	ft_printf("%s\n", str);
	free_memory(c);
	exit (EXIT_FAILURE);
}

void	free_memory(t_cub *c) //libera toda la memoria
{
	ft_printf("OLA\n");
	
	mlx_destroy_window(c->mlx, c->win);

	ft_printf("OLA\n");
	
	if (c->p)
		free(c->p);
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
	
	ft_printf("OLA\n");
	//...
	
	if (c)
		free(c);
}