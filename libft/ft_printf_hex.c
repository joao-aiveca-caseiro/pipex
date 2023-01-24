/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:29:01 by jaiveca-          #+#    #+#             */
/*   Updated: 2022/12/07 18:55:15 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen_hex(unsigned long n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (n != 0)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

void	ft_putnbr_hex(unsigned long n, char c)
{
	char	*base;

	if (c == 'u')
		base = "0123456789ABCDEF";
	else if (c == 'l')
		base = "0123456789abcdef";
	if (n > 15)
	{
		ft_putnbr_hex(n / 16, c);
		ft_putnbr_hex(n % 16, c);
	}
	else
		ft_putchar_fd(base[n], 1);
}

int	ft_printf_hex(char c, long n)
{
	if (c == 'x')
		ft_putnbr_hex(n, 'l');
	else if (c == 'X')
		ft_putnbr_hex(n, 'u');
	return (ft_numlen_hex(n));
}

int	ft_printf_hexvoid(unsigned long n)
{
	if (!n)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	ft_putnbr_hex(n, 'l');
	return (ft_numlen_hex(n) + 2);
}
