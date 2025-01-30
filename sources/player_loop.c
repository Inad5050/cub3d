/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:44:08 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/30 13:49:00 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	handle_player_input(void *param)
{	
	t_cub	*c;
	
	c = (t_cub *)param;
	c->p_walkdirection = 0;
	c->p_strafedirection = 0;
	c->p_turndirection = 0;
	if (mlx_is_key_down(c->mlx, MLX_KEY_ESCAPE))
		return(c_close(c), 0);
	else if (mlx_is_key_down(c->mlx, MLX_KEY_W))
		return(c->p_walkdirection = 1, update_player_position(c));
	else if (mlx_is_key_down(c->mlx, MLX_KEY_S))
		return(c->p_walkdirection = -1, update_player_position(c));
	else if (mlx_is_key_down(c->mlx, MLX_KEY_A))
		return(c->p_strafedirection = 1, update_player_position(c));
	else if (mlx_is_key_down(c->mlx, MLX_KEY_D))
		return(c->p_strafedirection = -1, update_player_position(c));
	else if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT))
		return(c->p_turndirection = -1, rotate_player(c));
	else if (mlx_is_key_down(c->mlx, MLX_KEY_RIGHT))
		return(c->p_turndirection = 1, rotate_player(c));
	return (0);
}

//actualiza el angulo (c->p_rotationangle) y la posicion del jugador (c->p_y)(c->p_x)

int	update_player_position(t_cub *c)
{
	float	movestep; //movimiento en el eje de la camara
	float	strafestep; //movimiento perpendicular al eje de la camara
	float	new_p_x;
	float	new_p_y;

/* 	c->p_rotationangle = normalize_angle(c->p_rotationangle + \
	c->p_turndirection * c->p_turnspeed); */
	movestep = c->p_walkdirection * c->p_walkspeed;
	strafestep = c->p_strafedirection * c->p_walkspeed;
	new_p_x = c->p_x + cos(c->p_rotationangle) * movestep + \
	cos(c->p_rotationangle + PI / 2) * strafestep;
	new_p_y = c->p_y + sin(c->p_rotationangle) * movestep + \
	sin(c->p_rotationangle + PI / 2) * strafestep;
	if (!check_wall_collision(c, new_p_x, c->p_y) && 
	!check_wall_collision(c, new_p_x - c->p_walkdirection * PLAYER_SIZE / 2, c->p_y))
			c->p_x = new_p_x; //comprueba que el borde de la figura del personaje no choque contra la pared (solo hay que comprobar un borde, el borde en la direccion del desplazamiento [c->p_walkidirection])
	if (!check_wall_collision(c, c->p_x, new_p_y) && 
	!check_wall_collision(c, c->p_x, new_p_y - c->p_strafedirection * PLAYER_SIZE / 2))
			c->p_y = new_p_y;
	return (0);
}

int	rotate_player(t_cub *c)
{
	c->p_rotationangle = normalize_angle(c->p_rotationangle + \
	c->p_turndirection * c->p_turnspeed);
	return (0);	
}

int	check_wall_collision(t_cub *c, float new_x, float new_y)
{
	int		map_x;
	int		map_y;
	int		offset_x;
	int		offset_y;

	offset_y = -1;
	while (offset_y <= 1)
	{
		offset_x = -1;
		while (offset_x <= 1)
		{
			map_x = ((int)(new_x + offset_x * 0.1) / TILE_SIZE); //comprobamos el espacio antes (offset -1), después (offset 1) y exactamente en la coordenada (offset 0)
			map_y = ((int)(new_y + offset_y * 0.1) / TILE_SIZE);
			if (map_y >= 0 && map_x >= 0 && map_y < c->map_axis_y && \
			map_x < (int)ft_strlen(c->map[map_y])) //comprobamos si las nuevas coordenadas estan en los limites del mapa
			{
				if (c->map[map_y][map_x] != '0') //comprobamos si las nuevas coordenadas son accesibles
					return (1); //si alguna de las tres coordenadas (offset -1, 0, 1) no es accesible devolvemos error (1)
			}
			offset_x++;
		}
		offset_y++;
	}
	return (0); //si superamos las 3 pruebas devolvemos 0
}
