/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:34:23 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/30 11:56:47 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* The function space_verification checks whether a given character c 
is a type of whitespace character. It returns 1
if c is any of the following characters, and 0 */

int	space_verification(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}
/* Calculate the lenth of the given array*/
int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
/* Printing error msg and exit the program */
void error_exit()
{
	printf("Error!\n");
	exit(1);
}
/* Verificate the color string if valid or not */
int is_number(const char *str)
{
    if (!str || *str == '\0' || *str =='\n')
        return (0);

    while (*str == ' ' || *str == '\t')
        str++;

    if (*str == '\0' || *str == '\n')
        return (0);
    while (*str >= '0' && *str <= '9')
        str++;
    while (*str == ' ' || *str == '\t')
		str++;
	if (*str != '\n' && *str != '\0')
		return(0);
    return (1); 
}
void	set_initial_position(t_player_position *player_position, int x, int y,
		char orientation)
{
	player_position->x = x;
	player_position->y = y;
	player_position->orientation = orientation;
	printf("Start position: %d, %d, %c\n", player_position->x,
		player_position->y, player_position->orientation);
}
