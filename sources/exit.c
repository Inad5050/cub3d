/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:30:49 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/30 16:36:28 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	c_error(char *str, t_cub *c)
{
	ft_printf("%s\n", str);		
	mlx_close_window(c->mlx);
	mlx_terminate(c->mlx);
	free_memory(c);
	exit (EXIT_FAILURE);
}

void	c_close(t_cub *c)
{	
	mlx_close_window(c->mlx);
	mlx_terminate(c->mlx);
	free_memory(c);
	exit(EXIT_SUCCESS);
}

void	free_memory(t_cub *c) //libera toda la memoria
{	
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
