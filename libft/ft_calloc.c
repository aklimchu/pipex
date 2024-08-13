/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:13:55 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/22 12:58:04 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;
	size_t	i;

	if (count && size && SIZE_MAX / size < count)
		return ((void *) 0);
	arr = (void *)malloc(count * size);
	if (arr == NULL)
		return ((void *) 0);
	i = 0;
	while (i < count * size)
	{
		*(unsigned char *)arr = 0;
		arr++;
		i++;
	}
	return (arr - count * size);
}
