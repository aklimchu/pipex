/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:46:17 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/06 11:18:24 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	int		*p;

	i = 0;
	p = NULL;
	if (dst == NULL && src != NULL)
		*p = 10;
	if (dst == NULL && src == NULL)
		return ((void *) 0);
	while (i < n)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst++;
		src++;
		i++;
	}
	return (dst - i);
}
