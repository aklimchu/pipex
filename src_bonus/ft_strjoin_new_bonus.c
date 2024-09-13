/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_new_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:53 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/04 08:24:29 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

//The function returns a new string formed my joined 3 strings provided by user
char	*ft_strjoin_new(char const *s1, char const *s2, char const *s3)
{
	char	*new_s;
	size_t	totallen;

	totallen = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	new_s = (char *)malloc((totallen + 1) * sizeof(char));
	if (new_s == NULL)
		return ((void *)0);
	while (*s1)
		*(new_s++) = *(s1++);
	while (*s2)
		*(new_s++) = *(s2++);
	while (*s3)
		*(new_s++) = *(s3++);
	*new_s = '\0';
	return (new_s - totallen);
}
