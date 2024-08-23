/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:50:23 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/23 15:31:31 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_m(char **new_s, size_t i); // divide only to 2 substrings

static size_t	nextc(char const *s, char c);

//static size_t	new_count(char const *s, char c);

char	**ft_split_new(char const *s, char c, int str_num)
{
	char	**new_s;
	int	i;

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

/* static size_t	new_count(char const *s, char c)
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
} */

/* int	main(void)
{
	char str[] = "grep str = NULL";

	char **str_new = ft_split_new(str, ' ', 7);
	int i = 0;
	while (str_new[i])
		ft_printf("%s\n", str_new[i++]);
	return(0);
} */