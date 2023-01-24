/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:36:30 by jaiveca-          #+#    #+#             */
/*   Updated: 2022/11/01 01:46:07 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	ch;

	i = 0;
	ptr = (unsigned char *) str;
	ch = (unsigned char) c;
	while (i < n)
	{
		if (ptr[i] == ch)
			return ((unsigned char *)(ptr + i));
		i++;
	}
	return (NULL);
}
