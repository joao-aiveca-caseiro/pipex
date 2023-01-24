/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:52:15 by jaiveca-          #+#    #+#             */
/*   Updated: 2022/10/28 13:51:13 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	char			*ptr1;
	char			*ptr2;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	ptr1 = (char *) str1;
	ptr2 = (char *) str2;
	if (n == 0)
		return (0);
	while (i < (n - 1) && ptr1[i] == ptr2[i])
		i++;
	c1 = ptr1[i];
	c2 = ptr2[i];
	return (c1 - c2);
}
