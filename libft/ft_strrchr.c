/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:05:02 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/06 10:36:49 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	slen;
	size_t	i;
	char	new_c;

	new_c = c + '\0';
	i = 0;
	slen = ft_strlen(s);
	s = s + slen;
	if (*s == new_c)
		return ((char *) s);
	while (i < slen)
	{
		s--;
		if (*s == new_c)
			return ((char *) s);
		i++;
	}
	return ((void *) 0);
}
