/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:28:35 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/06 10:33:22 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	totallen;
	size_t	i;
	size_t	dstlen;

	i = 0;
	totallen = ft_strlen(dst) + ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstsize < dstlen)
		return (dstsize + ft_strlen(src));
	while (*dst)
		dst++;
	while (i + 1 < dstsize - dstlen && *src)
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	*dst = '\0';
	return (totallen);
}
