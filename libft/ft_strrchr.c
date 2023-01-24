/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:58:18 by jaiveca-          #+#    #+#             */
/*   Updated: 2022/11/01 18:23:59 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				len;
	unsigned char	ch;

	len = ft_strlen(str);
	ch = (unsigned char) c;
	while (len >= 0)
	{
		if (str[len] == ch)
			return ((char *)(str + len));
		len--;
	}
	return (NULL);
}
