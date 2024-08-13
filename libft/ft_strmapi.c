/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:34:13 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/22 13:23:44 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_s;
	size_t	i;

	new_s = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (new_s == NULL)
		return ((void *)0);
	i = 0;
	while (*s)
	{
		*new_s = (*f)(i, *s);
		new_s++;
		s++;
		i++;
	}
	*new_s = '\0';
	return (new_s - i);
}
