/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/12 20:31:30 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../mlx/include/MLX42/MLX42.h"

typedef struct s_cube
{
	mlx_t			*mlx;

	double			time;

	const char		*png_floor;
	mlx_texture_t	*texture_floor;
	mlx_image_t		*img_floor;
	
	const char		*png_roof;
	mlx_texture_t	*texture_roof;	
	mlx_image_t		*img_roof;


} t_cube;

//errors
void	free_memory(t_cube *c);
void	free_img(t_cube *c);

//free_memory
void	c_error(char *str, t_cube *c);
void	c_error_img(char *str, t_cube *c)

//hooks
void	set_hooks(t_cube *c);

//initiate_struct
int		initiate_cube(t_cube *c);

//images
void	load_images(t_cube *c);
void	draw_images(t_cube *c);

#endif
