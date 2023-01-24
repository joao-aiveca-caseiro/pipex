/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:37:04 by jaiveca-          #+#    #+#             */
/*   Updated: 2022/11/01 18:21:14 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char) c;
	while (str[i])
	{
		if (str[i] == ch)
			return ((char *)(str + i));
		i++;
	}
	if (str[i] == ch)
		return ((char *)(str + i));
	return (NULL);
}
