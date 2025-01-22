/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:04:02 by dani              #+#    #+#             */
/*   Updated: 2025/01/20 13:39:30 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	render_3Dmap(t_cub *c) //recorre la matriz con cada byte en la que hemos escrito durante el proceso de ray casting
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDHT)
			select_3Dmap(y, x++, c);
		y++;
	}
}

void	select_3Dmap(int y, int x, t_cub *c) //seleccionamos el color para cada elemento del mapa
{
	if (c->map_3D[y * WIN_HEIGHT + x] == FLOOR)
		print_3Dmap(y, x, BLUE, c);
	else if (c->map_3D[y * WIN_HEIGHT + x] == WALL)
		print_3Dmap(y, x, GREEN, c);
	else if (c->map_3D[y * WIN_HEIGHT + x] == CEILLING)
		print_3Dmap(y, x, WHITE, c);
}

void	print_3Dmap(int y, int x, int color, t_cub *c)
{
	mlx_pixel_put(c->mlx, c->win_mlx_3D, x, y, color);
}

/* int	atoi_base(char *hex)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (hex[i])
	{
		if ('0' <= hex[i] && hex[i] <= '9')
			num = num * 16 + (hex[i] - '0');
		else if ('A' <= hex[i] && hex[i] <= 'F')
			num = num * 16 + (hex[i] - 'A' + 10);
		else
			return (-1);
		i++;
	}
	return (num);
} */

/* void	select_3Dmap(int y, int x, t_cub *c) //seleccionamos el color para cada elemento del mapa
{
	if (c->map_3D[y * WIN_HEIGHT + x] == FLOOR)
		print_3Dmap(y, x, modify_alpha(BLUE, x, c), c);
	else if (c->map_3D[y * WIN_HEIGHT + x] == WALL)
		print_3Dmap(y, x, modify_alpha(GREEN, x, c), c);
	else if (c->map_3D[y * WIN_HEIGHT + x] == CEILLING)
		print_3Dmap(y, x, modify_alpha(WHITE, x, c), c);
} */

// En 0x00FFFFFF cada uno de los digitos hexadecimales (de detras de la x) representa 4 digitos binarios. 
// Es una forma mas compacta de representar el valor de un color en notacion binaria. Si no (el color azul por ejemplo 0x000000FF) se veria asi 00000000 00000000 00000000 11111111. 8 bits forman un byte, un numero hexadecimal puede representar un byte con dos digitos.
// 0x es el prefijo que por convencion llevan los numeros hexadecimales y sirve para que el compilador los reconozca y no los confunda con decimales
// El operador | en C compara cada bit de dos operandos y establece el bit correspondiente del resultado a 1 si al menos uno de los bits de entrada es 1. De lo contrario, el resultado será 0.
// El operador & hace lo mismo salvo que ambos bits deben ser 1 o de lo contrario establece el valor en 0.
// El operador << desplaza los bits a posiciones más significativas, aumentando el valor del numero. Por ejemplo: 0xF = 15(en decimal) = 00000000 00000000 00000000 00001111 (en binario)(mostrando los 4 bytes relevantes para nuestra funcion)
// Al desplazarlo 24 bits se que da como 00001111 00000000 00000000 00000000. Ahora su valor incide directamente sobre los digitos que relevantes para determinar el alpha del color.

/* int	modify_alpha(int color, int x, t_cub *c) //modificamos el alpha del objeto en funcion de su distancia al jugador. Cuanto m
{
	int	new_alpha;

	color  =  color & 0x00FFFFFF; //ponemos a 0 los bits con los valores originales de alpha
	new_alpha = //establecer el nuevo valor de alpha en funcion de la ditancia del pixel
	color = (new_alpha << 24) | (color & 0x00FFFFFF); //desplaza los bits de alpha a las posiciones mas significativas y los suma a los de 'color', cuyos bits que dan valor a alpha han sido previamente limpiados
	return (color);
} */

/* int	atoi_base(char *hex)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (hex[i])
	{
		if ('0' <= hex[i] && hex[i] <= '9')
			num = num * 16 + (hex[i] - '0');
		else if ('A' <= hex[i] && hex[i] <= 'F')
			num = num * 16 + (hex[i] - 'A' + 10);
		else
			return (-1);
		i++;
	}
	return (num);
} */
