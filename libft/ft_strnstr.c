/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:05:08 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/06 11:41:22 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	size_t	i;

	nlen = ft_strlen(needle);
	i = 0;
	if (nlen == 0)
		return ((char *) haystack);
	if (len == 0 || nlen > ft_strlen(haystack))
		return ((void *) 0);
	if (len >= 10000000)
		len = ft_strlen(haystack);
	while (i + nlen < len + 1)
	{
		if (ft_strncmp(haystack, needle, nlen) == 0)
			return ((char *) haystack);
		haystack++;
		i++;
	}
	return ((void *) 0);
}
