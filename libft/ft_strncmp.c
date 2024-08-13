/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:24:24 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/06 10:35:26 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (*s1 && *s2 && i < n)
	{
		if (*(unsigned char *) s1 > *(unsigned char *) s2)
			return (1);
		if (*(unsigned char *) s1 < *(unsigned char *) s2)
			return (-1);
		s1++;
		s2++;
		i++;
	}
	if (i < n && *(unsigned char *) s1 > *(unsigned char *) s2)
		return (1);
	if (i < n && *(unsigned char *) s1 < *(unsigned char *) s2)
		return (-1);
	return (0);
}
