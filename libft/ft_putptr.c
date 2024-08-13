/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:00:04 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/22 12:17:47 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(void *ptr, int count)
{
	unsigned long	addr;
	char			buffer[20];
	char			*buff_ptr;
	char			*hex_digits;

	hex_digits = "0123456789abcdef";
	addr = (unsigned long)ptr;
	buff_ptr = buffer + sizeof(buffer) - 1;
	*buff_ptr = '\0';
	if (!addr)
		*--buff_ptr = '0';
	while (addr)
	{
		*--buff_ptr = hex_digits[addr % 16];
		addr /= 16;
	}
	*--buff_ptr = 'x';
	*--buff_ptr = '0';
	if (ft_putstr(buff_ptr, count) == -1)
		return (-1);
	return (count + ft_strlen(buff_ptr));
}

// the funtion prints (void *) pointer argument in hexadecimal format
