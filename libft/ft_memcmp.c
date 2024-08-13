/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:43:27 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/06 10:26:09 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	temp1;
	unsigned char	temp2;

	i = 0;
	while (i < n)
	{
		temp1 = *(unsigned char *)s1;
		temp2 = *(unsigned char *)s2;
		if (temp1 != temp2)
			return (temp1 - temp2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}
