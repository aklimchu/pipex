/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:33:38 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/22 12:52:06 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_checkchar(char format)
{
	char	*set;

	set = "cspdiuxX%";
	while (*set)
	{
		if (*set == format)
			return (1);
		set++;
	}
	return (0);
}
