/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:00 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/01/30 15:18:27 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cmd_parsing(char **envp)
{
	int		i;
	int		j;
	char	*envp_path;
	char	**split_paths;

	i = 0;
	j = 0;
	envp_path = NULL;

	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != NULL)
		{
			envp_path = ft_substr(envp[i], 5, 1000);
			break ;
		}
		i++;
	}
	split_paths = ft_split(envp_path, ':');
	i = 0;
	j = 0;
	while (split_paths[i])
	{
		while (split_paths[i][j])
			j++;
		split_paths[i][j] = '/';
		split_paths[i][j + 1] = '\0';
		j = 0;
		i++;
	}
	i = 0;
	return (split_paths);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile_fd;
	int		outfile_fd;
	int		i;
	char	**split_paths;
	char	**cmd_args;
	char	*cmd;

	split_paths = cmd_parsing(envp);
	cmd_args = ft_split(argv[3], ' ');
	i = 0;
	while (split_paths[i])
	{
		cmd = ft_strjoin(split_paths[i], argv[2]);
		if (execve(cmd, cmd_args, envp) == -1)
		{
			perror("Error");
			free(cmd);
		}
		else
			break ;
		i++;
	}
	if (argc > 4)
	{
		infile_fd = open(argv[1], O_RDWR);
		if (infile_fd == -1)
			perror("Error");
		outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT);
	}
}
