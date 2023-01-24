/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:14:30 by jaiveca-          #+#    #+#             */
/*   Updated: 2022/11/01 15:08:37 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (big == NULL && len == 0)
		return (NULL);
	if (little[i] == '\0')
		return ((char *) big);
	while (big[i] && i < len)
	{
		while (big[i + n] && (i + n) < len && big[i + n] == little[n])
			n++;
		if (little[n] == '\0')
			return ((char *)(big + i));
		i++;
		n = 0;
	}
	return (NULL);
}
