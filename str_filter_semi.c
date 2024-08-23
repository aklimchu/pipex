/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_filter_semi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:44:40 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/23 14:26:01 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	checklen(char *str)
{
	int		i;
	char	temp;

	i = 2;
	temp = *str;
	str++;
	while (*(str + 1))
	{
		if (*str == '"' && temp != ' ' && *(str + 1) != ' ')
		{
			temp = *str;
			str++;
		}
		else
		{
			temp = *str;
			i++;
			str++;
		}
	}
	return (i);
}

char	*str_filter_semi(char *s1)
{
	size_t	newlen;
	size_t	len;
	char	*new_s;
	char	temp;

	len = ft_strlen(s1);
	newlen = checklen(s1);
	new_s = (char *)malloc((newlen + 1) * sizeof(char));
	if (new_s == NULL)
		return ((void *)0);
	temp = *s1;
	*new_s = *s1;
	new_s++;
	s1++;
	while (*(s1 + 1))
	{
		if (*s1 == '"' && temp != ' ' && *(s1 + 1) != ' ')
		{
			temp = *s1;
			s1++;
		}
		else
		{
			*new_s = *s1;
			temp = *s1;
			new_s++;
			s1++;
		}
	}
	*new_s = *s1;
	new_s++;
	*new_s = '\0';

	free(s1 - (len - 1));	//	add this freeing when working with pipex
	return (new_s - newlen);
}

/* int main (int argc, char *argv[])
{
	char set[3];
	//set[0] = '"';
	set[0] = 92;
	set[1] = '\0';
	char str[6];
	str[0] = 'g';
	str[1] = 'r';
	str[2] = 'e';
	str[3] = 92;
	str[4] = 'p';
	str[5] = '\0';
	
	char str2[5];
	str2[0] = 'c';
	str2[1] = 'a';
	str2[2] = '"';
	str2[3] = 92;
	str2[4] = '\0';

	ft_printf("%s\n", str_filter_semi(str));
	ft_printf("%s\n", str_filter_semi(str2));
	ft_printf("%s\n", str_filter_semi(argv[1]));
	ft_printf("%s\n", str_filter_semi(argv[2]));

} */