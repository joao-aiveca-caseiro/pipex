/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:26:21 by jaiveca-          #+#    #+#             */
/*   Updated: 2022/12/07 18:55:25 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	ft_putnbr_long(long n)
{
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		ft_putnbr_long(-n);
	}
	else if (n > 9)
	{
		ft_putnbr_long(n / 10);
		ft_putnbr_long(n % 10);
	}
	else
		ft_putchar_fd(n + 48, 1);
}

int	ft_printf_int(long n)
{
	ft_putnbr_long(n);
	return (ft_numlen(n));
}
