/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:42:28 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/22 13:03:53 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	checkc(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static size_t	checkstr(char const *s1, char const *set)
{
	size_t		i;

	i = 0;
	while (*s1)
	{
		if (checkc(*s1, set) == 1)
			i++;
		s1++;
	}
	return (i);
}

static size_t	checklen(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (checkc(*s1, set) == 1)
		s1++;
	while ((*s1) && checkstr(s1, set) != ft_strlen(s1))
	{
		s1++;
		i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	newlen;
	char	*new_s;

	newlen = checklen(s1, set);
	new_s = (char *)malloc((newlen + 1) * sizeof(char));
	if (new_s == NULL)
		return ((void *)0);
	while (checkc(*s1, set) == 1)
		s1++;
	while ((*s1) && checkstr(s1, set) != ft_strlen(s1))
	{
		*new_s = *s1;
		new_s++;
		s1++;
	}
	*new_s = '\0';
	return (new_s - newlen);
}
