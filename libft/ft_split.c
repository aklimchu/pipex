/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:28:07 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/22 13:01:53 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_m(char **new_s, size_t i)
{
	size_t	count;

	count = 0;
	while (count <= i)
	{
		free(new_s[count]);
		count++;
	}
	free(new_s);
	return ;
}

static size_t	nextc(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s != c && (*s))
	{
		s++;
		i++;
	}
	return (i);
}

static size_t	new_count(char const *s, char c)
{
	size_t	i;	

	i = 1;
	if (*s != c && (*s))
	{
		i++;
		s++;
	}
	while (*s && *(s + 1))
	{
		if (*s == c && *(s + 1) != c)
			i++;
		s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**new_s;
	size_t	i;

	new_s = (char **)malloc(new_count(s, c) * sizeof(char *));
	if (new_s == NULL)
		return ((void *) 0);
	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			new_s[i] = ft_substr(s, 0, nextc(s, c));
			if (new_s[i] == NULL)
			{
				free_m(new_s, i);
				return (NULL);
			}
			i++;
			s = s + nextc(s, c);
		}
	}
	new_s[i] = ((void *) 0);
	return (new_s);
}
