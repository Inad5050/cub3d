/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:42:54 by dangonz3          #+#    #+#             */
/*   Updated: 2025/02/06 15:55:58 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

float	normalize_angle(float angle) //hace que el angulo sea positivo y menor a 360 (2PI) grados
{
	angle = remainder(angle, 2 * PI); //hace el equivalente a angle % 2PI, pero con decimales (float) en lugar de ints
	if (angle < 0)
		angle = angle + 2 * PI; //si el angulo es negativo obtenemos el equivalente positivo sumandole 2PI que equivale a 360 grados
	return (angle);
}

uint32_t	get_color(uint8_t *ptr) //load_png almacena el valor del color de los pixeles en estructuras de 4 integers de 8 bytes. Queremos combinar esos numeros en uno solo de 32 bytes.
{
	uint32_t	b; //blue
	uint32_t	g; //green
	uint32_t	r; //red
	uint32_t	a; //alpha. transparencia
	
	r = (uint32_t)*(ptr);
	g = (uint32_t)*(ptr + 1);
	b = (uint32_t)*(ptr + 2);
	a = (uint32_t)*(ptr + 3);
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

uint32_t	get_color_alt(int *ptr) //en el archivo .cub definimos el color del techo y el suelo como integers de 3 ints (cada int tiene 8 bytes). para ajustarlo al formato que usaremos más delante añadimos el canal alpha 
{
	uint32_t	b; //blue
	uint32_t	g; //green
	uint32_t	r; //red
	uint32_t	a; //alpha. transparencia

	r = (uint32_t)ptr[0];
	g = (uint32_t)ptr[1];
	b = (uint32_t)ptr[2];
	a = (uint32_t)255;
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))); //teorema de pitagoras	
}
