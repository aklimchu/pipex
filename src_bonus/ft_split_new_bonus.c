/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:50:23 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/04 08:24:16 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static char		**free_m(char **new_s, size_t i);

static size_t	nextc(char const *s, char c);

//The function splits a string s to selected number of substrings
//with the character c, used as delimiter
char	**ft_split_new(char const *s, char c, int str_num)
{
	char	**new_s;
	int		i;

	new_s = (char **)malloc((str_num + 1) * sizeof(char *));
	if (new_s == NULL)
		return ((void *) 0);
	i = 0;
	while ((*s) && i < str_num)
	{
		if (*s == c)
			s++;
		else
		{
			if (i < str_num - 1)
				new_s[i] = ft_substr(s, 0, nextc(s, c));
			else
				new_s[i] = ft_substr(s, 0, ft_strlen(s));
			if (new_s[i] == NULL)
				return (free_m(new_s, i));
			i++;
			s = s + nextc(s, c);
		}
	}
	new_s[i] = ((void *) 0);
	return (new_s);
}

static char	**free_m(char **new_s, size_t i)
{
	size_t	count;

	count = 0;
	while (count <= i)
	{
		free(new_s[count]);
		count++;
	}
	free(new_s);
	return ((void *) 0);
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
