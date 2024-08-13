/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 08:37:21 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/22 12:50:01 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c, int count)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (count + 1);
}

// the program prints a single character

int	ft_putstr(char *str, int count)
{
	if (!str)
	{
		count = ft_putstr("(null)", count);
		if (count == -1)
			return (-1);
	}
	while (str && *str != '\0')
	{
		if (write (1, str, 1) == -1)
			return (-1);
		str = str + 1;
		count++;
	}
	return (count);
}

// the function prints a string

static int	ft_putnbr(int nb, int count)
{
	if (nb == -2147483648)
	{
		count = ft_putchar('-', count);
		if (count == -1)
			return (-1);
		count = ft_putchar('2', count);
		if (count == -1)
			return (-1);
		nb = 147483648;
	}
	if (nb < 0)
	{
		count = ft_putchar('-', count);
		if (count == -1)
			return (-1);
		nb *= -1;
	}
	count = ft_putnbr_ui(nb, count);
	return (count);
}

// the function prints an integer in base 10

static int	ft_printformat(va_list args, char format, int count)
{
	char	ch;

	if (format == 'c')
	{
		ch = va_arg(args, int);
		count = ft_putchar(ch, count);
	}
	if (format == 's')
		count = ft_putstr(va_arg(args, char *), count);
	if (format == 'p')
		count = ft_putptr(va_arg(args, void *), count);
	if (format == 'i' || format == 'd')
		count = ft_putnbr(va_arg(args, int), count);
	if (format == 'u')
		count = ft_putnbr_ui(va_arg(args, unsigned int), count);
	if (format == 'x' || format == 'X')
		count = ft_puthex(va_arg(args, long int), format, count);
	if (format == '%')
		count = ft_putchar('%', count);
	return (count);
}

// the function processes the arguments of the variadic function
// and calls helper function to print the argument depanding on the
// type of the argument

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && ft_checkchar(*(format + 1)) == 1)
		{
			format++;
			count = ft_printformat(args, *format++, count);
		}
		else
			count = ft_putchar(*format++, count);
		if (count == -1)
			return (-1);
	}
	va_end(args);
	return (count);
}

// the variadic function receives the arguments (args is
// a pointer to the last fixed argument) and passes them
// to ft_printfformat for further processing
// "count" is a variable used for counting the number of printed characters