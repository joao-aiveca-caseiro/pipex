/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:00 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/01 16:40:57 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_splitter(char *envp_path)
{
	char	**split_paths;
	int		i;
	int		j;

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
	return (split_paths);
}

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
	split_paths = path_splitter(envp_path);
	return (split_paths);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile_fd;
//	int		outfile_fd;
	int		i;
	char	**split_paths;
	char	**cmd_args;
	char	*cmd;

	if (argc > 4)
	{
		infile_fd = open(argv[1], O_RDWR);
		if (infile_fd == -1)
			perror("Error");
	//	outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT);
		dup2(infile_fd, STDIN_FILENO);
		split_paths = cmd_parsing(envp);
		cmd_args = ft_split(argv[2], ' ');
		i = 0;
		while (split_paths[i])
		{
			cmd = ft_strjoin(split_paths[i], cmd_args[0]);
			if (execve(cmd, cmd_args, envp) == -1)
			{
				perror("Error");
				free(cmd);
			}
			else
				break ;
			i++;
		}
	}
}
