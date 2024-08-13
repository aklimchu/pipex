/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:39:51 by aklimchu          #+#    #+#             */
/*   Updated: 2024/06/26 13:48:07 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static const char	*whites(const char *str)
{
	while ((*str == 32) || (*str > 8 && *str < 14))
		str++;
	if (*str == 43 && *(str + 1) == 45)
		return (str);
	else if (*str == 43)
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	int			res;
	int			neg;
	long int	checkl;

	res = 0;
	neg = 1;
	checkl = 0;
	str = whites(str);
	if (*str == 45)
	{
		neg = neg * (-1);
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		checkl = checkl * 10 + (*str - '0');
		if (checkl < 0 && neg == 1)
			return (-1);
		if (checkl < 0 && neg == -1)
			return (0);
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * neg);
}
