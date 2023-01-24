/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:33:12 by jaiveca-          #+#    #+#             */
/*   Updated: 2022/12/07 18:55:35 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = -1;
	len = 0;
	va_start(args, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i += 1;
			len += ft_printf_args(args, format[i]);
		}
		else if (format[i] != '%')
		{
			ft_putchar_fd(format[i], 1);
			len++;
		}
	}
	va_end(args);
	return (len);
}

int	ft_printf_args(va_list args, char f)
{
	int	len;

	len = 0;
	if (f == 'c')
		len += ft_printf_char(va_arg(args, int));
	else if (f == 's')
		len += ft_printf_str(va_arg(args, char *));
	else if (f == 'i' || f == 'd')
		len += ft_printf_int(va_arg(args, int));
	else if (f == 'u')
		len += ft_printf_int(va_arg(args, unsigned int));
	else if (f == 'x' || f == 'X')
		len += ft_printf_hex(f, va_arg(args, unsigned int));
	else if (f == 'p')
		len += ft_printf_hexvoid(va_arg(args, unsigned long));
	else if (f == '%')
	{
		ft_putchar_fd('%', 1);
		len++;
	}
	return (len);
}
