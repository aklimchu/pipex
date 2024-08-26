/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:12:18 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/26 10:53:01 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	word_count(char *str);

int	count_param(char *str)
{
	int		i;

	i = 2;
	/* if (ft_strncmp(str, "awk", 3) == 0 && \
		(ft_strnstr(str, "-F", 6) || ft_strnstr(str, "-f", 6)))
		return (4);
	if (word_count(str) > 2 && ft_strchr(str, '-')) 
		return (3); */
	//if (ft_strncmp(str, "tar", 3) == 0)
	if (ft_strnstr(str, "grep", 4) && ft_strnstr(str, "-", 6) == 0)
		return (i);
	else
		return (word_count(str));
}

static int	word_count(char *str)
{
	int		count;
	int		flag;
	
	count = 1;
	flag = 0;
	while (*str)
	{
		if (*str == '{')
			flag = 1;
		if (*str == '}')
			flag = 0;	
		if (*str == ' ' && *(str + 1) != ' ' && flag == 0)
			count++;
	str++;
	}
	return(count);
}