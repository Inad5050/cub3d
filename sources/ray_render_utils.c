/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:26:02 by dangonz3          #+#    #+#             */
/*   Updated: 2025/01/27 16:26:13 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* uint32_t	get_color(uint8_t *p) //La función convierte cuatro componentes de color RGBA de 8 bits en un único valor de 32 bits. Esto permite representar un color completo en un solo entero, lo que es útil para almacenar o procesar datos gráficos de manera compacta y eficiente.
{
	uint32_t	b; // uint8_t es un unsigned integer de 8 bits. uint32_t es un unsigned integer de 32 bits.
	uint32_t	g;
	uint32_t	r;
	uint32_t	a;

	r = (uint32_t) *(p); //accedemos a cada puntero del array de uint8_t, los casteamos a uint32_t
	g = (uint32_t) *(p + 1);
	b = (uint32_t) *(p + 2);
	a = (uint32_t) *(p + 3);
	return ((r << 24) + (g << 16) + (b << 8) + a); //desplazamos los valores de cada uno y los sumamos para formar un solo entero de 32 bits
} */
