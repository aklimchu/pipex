/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:08:44 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/06 10:26:57 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*checknull(void *dst, const void *src)
{
	int		*p;

	p = NULL;
	if (dst == NULL && src != NULL)
		*p = 10;
	if (dst != NULL && src == NULL)
		*p = 10;
	if (dst == NULL && src == NULL)
		return ((void *) 0);
	return ("ALL GOOD");
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (checknull(dst, src) == NULL)
		return ((void *) 0);
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			*(unsigned char *)(dst + i) = *(const unsigned char *)(src + i);
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			*(unsigned char *)(dst + i - 1) = *(unsigned char *)(src + i - 1);
			i--;
		}
	}
	return (dst);
}
