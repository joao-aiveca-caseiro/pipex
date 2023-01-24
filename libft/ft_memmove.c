/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:12:41 by jaiveca-          #+#    #+#             */
/*   Updated: 2022/11/01 13:43:30 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)str1;
	s = (char *)str2;
	if (d == NULL && s == NULL)
		return (NULL);
	else if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	else
	{		
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (str1);
}
