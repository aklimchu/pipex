/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:07:02 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/27 14:02:55 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function implements the same behaviour as strchr from libc, checking
// also if input string is a NULL

char	*ft_strchr_new(const char *s, int c)
{
	char	new_c;

	if (s == NULL)
		return ((void *) 0);
	new_c = c + '\0';
	while (*s)
	{
		if (*s == new_c)
			return ((char *) s);
		s++;
	}
	if (*s == new_c)
		return ((char *) s);
	return ((void *) 0);
}

// The function implements the same behaviour as strncat from libc.

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	while (dest[i])
		i++;
	while (src[c] && c < nb)
	{
		dest[i] = src[c];
		i++;
		c++;
	}
	dest[i] = '\0';
	return (dest);
}
