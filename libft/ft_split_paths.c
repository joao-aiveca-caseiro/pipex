/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 00:19:21 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/13 16:22:40 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_substrlen(char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != sep)
		i++;
	return (i);
}

static int	strcount(char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

static char	*malloc_word(char *str, char sep)
{
	int		length;
	int		i;
	char	*word;

	i = 0;
	length = ft_substrlen(str, sep);
	word = malloc(sizeof(char) * (length + 2));
	while (i < length)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '/';
	word[i + 1] = '\0';
	return (word);
}

char	**ft_split_paths(char *s, char sep)
{
	char	**strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strs = malloc(sizeof(char *) * (strcount(s, sep) + 1));
	if (!strs)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == sep)
			s++;
		if (s[i] != '\0')
		{
			strs[j] = malloc_word(s, sep);
			j++;
		}
		while (s[i] != '\0' && s[i] != sep)
			s++;
	}
	strs[j] = 0;
	return (strs);
}
