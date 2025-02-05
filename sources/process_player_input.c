/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_player_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:44:08 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/30 13:49:00 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void mlx_cursor_hook(mlx_t* mlx, mlx_cursorfunc func, void* param);
//This function sets the cursor callback, which is called when the
//mouse position changes. Position is relative to the window.

void mlx_get_mouse_pos(mlx_t* mlx, int32_t* x, int32_t* y);
//Returns the current, relative, mouse cursor position on the window, starting
//from the top left corner.

void	process_player_input(void *param)
{	
	t_cub	*c;
	
	c = (t_cub *)param;
	c->p_walkdirection = 0;
	c->p_strafedirection = 0;
	c->p_turndirection = 0;
	c->p_turnspeed = c->p_turnspeed_original;
	if (mlx_is_key_down(c->mlx, MLX_KEY_ESCAPE))
		c_close(c);
	if (mlx_is_key_down(c->mlx, MLX_KEY_W))
		c->p_walkdirection = 1;
	if (mlx_is_key_down(c->mlx, MLX_KEY_S))
		c->p_walkdirection = -1;
	if (mlx_is_key_down(c->mlx, MLX_KEY_A))
		c->p_strafedirection = -1;
	if (mlx_is_key_down(c->mlx, MLX_KEY_D))
		c->p_strafedirection = 1;
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT))
		c->p_turndirection = -1;
	if (mlx_is_key_down(c->mlx, MLX_KEY_RIGHT))
		c->p_turndirection = 1;
	mouse_hook(c);
	update_player_position(c);
}

void	mouse_hook(t_cub *c)
{
	int32_t	x;
	int32_t y;

	if (c->p_turndirection)
		return;
	mlx_get_mouse_pos(c->mlx, &x, &y);
	if (0 < x && x <= WIN_WIDHT * 0.3)
	{
		c->p_turndirection = -1;
		if (x > WIN_WIDHT * 0.15)
			c->p_turnspeed *= 0.4;
	}
	if (WIN_WIDHT * 0.7 < x && x < WIN_WIDHT)
	{
		c->p_turndirection = 1;
		if (x < WIN_WIDHT * 0.85)
			c->p_turnspeed *= 0.4;
	}
}

void	update_player_position(t_cub *c)
{
	float	movestep; //movimiento en el eje de la camara
	float	strafestep; //movimiento perpendicular al eje de la camara
	float	new_p_x;
	float	new_p_y;

	c->p_rotationangle = normalize_angle(c->p_rotationangle + \
	c->p_turndirection * c->p_turnspeed); //si hemos girado aumentamos el angulo en c->p_turnspeed
	movestep = c->p_walkdirection * c->p_walkspeed; //su valor sera cero si no nos hemos movido en ese eje del jugador o sera igual a c->p_walkspeed si nos hemos movido en ese eje
	strafestep = c->p_strafedirection * c->p_walkspeed;
	new_p_x = c->p_x + cos(c->p_rotationangle) * movestep + \
	cos(c->p_rotationangle + PI / 2) * strafestep; //nos desplazamos en el eje x en funcion del delta de movestep y strafestep sobre el eje x. Este eje x existe en relaciṕm al mapa
	new_p_y = c->p_y + sin(c->p_rotationangle) * movestep + \
	sin(c->p_rotationangle + PI / 2) * strafestep;
	if (!check_wall_collision(c, new_p_x, c->p_y) && 
	!check_wall_collision(c, new_p_x - c->p_walkdirection * PLAYER_SIZE / 2, c->p_y))
			c->p_x = new_p_x; //comprueba que el borde de la figura del personaje no choque contra la pared (solo hay que comprobar un borde, el borde en la direccion del desplazamiento [c->p_walkidirection]). Restamos la mitad del tamaño del personaje, que es lo que sobresale por ese lado
	if (!check_wall_collision(c, c->p_x, new_p_y) && 
	!check_wall_collision(c, c->p_x, new_p_y - c->p_strafedirection * PLAYER_SIZE / 2))
			c->p_y = new_p_y;
}

int	check_wall_collision(t_cub *c, float new_x, float new_y)
{
	int		map_x;
	int		map_y;
	int		offset_x;
	int		offset_y;

	offset_y = -1;
	while (offset_y <= 1) //ambos while se repetiran 3 veces. comprobamos el espacio antes (offset -1), después (offset 1) y exactamente en la coordenada (offset 0)
	{
		offset_x = -1;
		while (offset_x <= 1)
		{
			map_x = ((int)(new_x + offset_x * 0.1) / TILE_SIZE); 
			map_y = ((int)(new_y + offset_y * 0.1) / TILE_SIZE);
			if (map_y >= 0 && map_x >= 0 && map_y < c->map_max_y && \
			map_x < (int)ft_strlen(c->map[map_y])) //comprobamos si las nuevas coordenadas estan en los limites del mapa
			{
				if (c->map[map_y][map_x] != '0') //comprobamos si las nuevas coordenadas son accesibles
					return (1); //si alguna de las tres coordenadas (offset -1, 0, 1) no es accesible, devolvemos error (1)
			}
			offset_x++;
		}
		offset_y++;
	}
	return (0); //si superamos las 3 pruebas devolvemos 0
}
