/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:36:32 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/16 09:36:59 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The function implements the same behaviour as strchr from libc.

char	*ft_strchr(const char *s, int c)
{
	char	new_c;

	new_c = c + '\0';
	while (*s)
	{
		if (*s == new_c)
			return ((char *) s);
		s++;
	}
	if (*s == new_c)
		return ((char *) s);
	return ((void *) 0);
}
