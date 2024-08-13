/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:36:32 by aklimchu          #+#    #+#             */
/*   Updated: 2024/04/29 15:51:12 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
