/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ui.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:58:25 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/22 08:39:23 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_ui(unsigned int nb, int count)
{
	if (nb >= 10)
	{
		count = ft_putnbr_ui(nb / 10, count);
		if (count == -1)
			return (-1);
		count = ft_putnbr_ui(nb % 10, count);
		if (count == -1)
			return (-1);
	}
	if (nb < 10)
	{
		count = ft_putchar(nb + '0', count);
		if (count == -1)
			return (-1);
	}
	return (count);
}

// the function prints an unsigned decimal (base 10) number.
