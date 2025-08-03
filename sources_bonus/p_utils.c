/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:34:23 by otboumeh          #+#    #+#             */
/*   Updated: 2025/02/21 12:33:51 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	space_verification(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	error_exit(void)
{
	printf("Error!\n");
	exit(1);
}

int	is_number(const char *str)
{
	if (!str || *str == '\0' || *str == '\n')
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
		return (0);
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
