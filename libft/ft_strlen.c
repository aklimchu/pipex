/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:30:03 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/16 09:38:34 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function implements the same behaviour as strlen from libc.

size_t	ft_strlen(const char *c)
{
	size_t		i;

	i = 0;
	while (*c)
	{
		i++;
		c++;
	}
	return (i);
}
