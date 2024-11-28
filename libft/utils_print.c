/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:42:52 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/26 09:43:20 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_puthexa_str(size_t n)
{
	char	buffer[17];
	int		i;
	char	*res;

	ft_memset(buffer, '\0', sizeof(buffer));
	i = 15;
	while (n > 0)
	{
		buffer[i] = HEXU[n % 16];
		n /= 16;
		i--;
	}
	res = strdup(&buffer[i + 1]);
	return (res);
}

char	*ft_putaddress_str(unsigned long p)
{
	char	*res;
	char	buffer[19];
	int		i;

	ft_memset(buffer, '\0', sizeof(buffer));
	i = 17;
	buffer[0] = '0';
	buffer[1] = 'x';
	while (p > 0)
	{
		buffer[i] = HEXU[p % 16];
		p /= 16;
		i--;
	}
	res = strdup(&buffer[i + 1]);
	return (res);
}

char	*str_or_null(const char *str)
{
	char	*out;

	if (!str)
		out = ft_strdup("(null)");
	else
		out = ft_strdup(str);
	return (out);
}