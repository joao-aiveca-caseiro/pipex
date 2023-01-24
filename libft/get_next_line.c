/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:14:11 by jaiveca-          #+#    #+#             */
/*   Updated: 2022/12/07 19:10:01 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_buffer(int fd, char *str)
{
	char	*buff;
	int		readbytes;

	buff = calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (NULL);
	readbytes = read(fd, buff, BUFFER_SIZE);
	if (readbytes <= 0)
	{
		if (!str[0])
		{
			free(str);
			str = NULL;
		}
	}
	while (readbytes > 0)
	{
		str = strjoin_gnl(str, buff);
		if (strchr_gnl(str) == 1)
			break ;
		readbytes = read(fd, buff, BUFFER_SIZE);
		buff[readbytes] = '\0';
	}
	free(buff);
	return (str);
}

char	*copy_until_nl(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = calloc_gnl(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (i + 1 > 0)
	{
		line[i] = str[i];
		i--;
	}
	return (line);
}

char	*trim_printed(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	newstr = calloc_gnl((strlen_gnl(str) - i), sizeof(char));
	if (!newstr)
		return (NULL);
	i++;
	while (str[i])
		newstr[j++] = str[i++];
	newstr[j] = '\0';
	free(str);
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char	*text[1024];
	char		*nline;

	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		if (text[fd])
		{
			free(text[fd]);
			text[fd] = NULL;
		}
		return (NULL);
	}
	if (!text[fd])
		text[fd] = calloc_gnl(1, sizeof(char));
	if (strchr_gnl(text[fd]) == 0)
		text[fd] = read_buffer(fd, text[fd]);
	nline = copy_until_nl(text[fd]);
	text[fd] = trim_printed(text[fd]);
	return (nline);
}

/*
# include <fcntl.h>

int	main(void)
{
	int fd = open("text", O_RDONLY);
	char	*s;
	
	s = get_next_line(fd);
	printf("Line 1:\n%s", s);
	free(s);
	s = get_next_line(fd);
	printf("Line 2:\n%s", s);
	free(s);
	s = get_next_line(fd);
	printf("Line 3:\n%s", s);
	free(s);
	s = get_next_line(fd);
	printf("Line 4:\n%s", s);
	free(s);
	s = get_next_line(fd);
	printf("Line 5:\n%s", s);
	free(s);
	close(fd);
}*/
