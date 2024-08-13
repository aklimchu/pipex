/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:29:58 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/22 12:57:32 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countd(int n)
{
	size_t	d;

	d = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = n * (-1);
	while (n > 0)
	{
		n = n / 10;
		d++;
	}
	return (d);
}

static char	*creates(size_t d, int n)
{
	char	*str;
	int		isneg;

	isneg = 0;
	if (n < 0)
		isneg = -1;
	str = (char *)malloc((d - isneg + 1) * sizeof(char));
	if (str == NULL)
		return ((void *)0);
	str = str + d - isneg;
	*str = '\0';
	str = str - d + isneg;
	if (isneg == -1)
		*str = '-';
	return (str);
}

static char	*writes(char *str, size_t d, int n)
{
	size_t	i;
	int		isneg;

	i = 0;
	isneg = 1;
	if (n < 0)
	{
		str++;
		isneg = -1;
	}
	str = str + d;
	while (i < d)
	{
		str--;
		*str = (n * isneg) % 10 + '0';
		n = n / 10;
		i++;
	}
	if (isneg == -1)
		str--;
	return (str);
}

static char	*ifmaxint(void)
{
	char	*str;

	str = (char *)malloc(12 * sizeof(char));
	if (str == NULL)
		return ((void *)0);
	*str = '-';
	*(str + 1) = '2';
	*(str + 2) = '1';
	*(str + 3) = '4';
	*(str + 4) = '7';
	*(str + 5) = '4';
	*(str + 6) = '8';
	*(str + 7) = '3';
	*(str + 8) = '6';
	*(str + 9) = '4';
	*(str + 10) = '8';
	*(str + 11) = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	d;
	char	*str;

	if (n == -2147483648)
	{
		str = ifmaxint();
		return (str);
	}
	d = countd(n);
	str = creates(d, n);
	if (str == NULL)
		return ((void *)0);
	str = writes(str, d, n);
	return (str);
}
