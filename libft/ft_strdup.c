/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:58:15 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/27 14:05:17 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
