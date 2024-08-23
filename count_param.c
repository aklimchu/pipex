/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:12:18 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/23 16:07:17 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	word_count(char *str);

int	count_param(char *str)
{
	int		i;

	i = 2;
	if (ft_strncmp(str, "awk", 3) == 0 && \
		(ft_strnstr(str, "-F", 6) || ft_strnstr(str, "-f", 6)))
		return (4);
	if (ft_strncmp(str, "tar", 3) == 0)
		return (word_count(str));
	if (word_count(str) > 2 && ft_strchr(str, '-')) 
		return (3);
	
	return (i);
}

static int	word_count(char *str)
{
	int		count;
	
	count = 1;
	while (*str)
	{
		if (*str == ' ' && (*str + 1) != ' ')
			count++;
	str++;
	}
	return(count);
}