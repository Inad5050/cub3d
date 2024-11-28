/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:19:16 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/24 11:32:10 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*output;

	start = 0;
	if (!s1)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (start == ft_strlen(s1))
	{
		output = (char *)ft_calloc(1, sizeof(char));
		if (!output)
			return (NULL);
		return (output);
	}
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	output = ft_substr(s1, start, (end - start) + 1);
	return (output);
}

/* int	main(void)
{
	char	*result = ft_strtrim("lorem \n ipsum \t dolor \n sit \t amet", " ");

	while (*result)
	{
		write(1, result, 1);
		result++;
	}
	return (0);
} */
