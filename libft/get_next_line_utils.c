/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:07:02 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/22 10:09:29 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function implements the same behaviour as strlen from libc.

size_t	ft_strlen(const char *c)
{
	size_t		i;

	i = 0;
	while (*c)
	{
		i++;
		c++;
	}
	return (i);
}

// The function implements the same behaviour as strchr from libc.

char	*ft_strchr(const char *s, int c)
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

// The function allocates (with malloc(3)) and returns a substring
// from the string ’s’.
// The substring begins at index ’start’ and is of maximum size ’len’.

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_s;
	unsigned int	i;

	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (new_s == NULL)
		return ((void *)0);
	if (start >= ft_strlen(s))
	{
		*new_s = '\0';
		return (new_s);
	}
	i = 0;
	while (i < len)
	{
		new_s[i] = s[i + start];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

// The function implements the same behaviour as strdup from libc.

char	*ft_strdup(const char *s1)
{
	char	*arr;
	size_t	slen;

	slen = ft_strlen(s1);
	arr = (char *)malloc((slen + 1) * sizeof(char));
	if (arr == NULL)
		return ((void *) 0);
	while (*s1)
	{
		*arr = *s1;
		arr++;
		s1++;
	}
	*arr = '\0';
	return (arr - slen);
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
