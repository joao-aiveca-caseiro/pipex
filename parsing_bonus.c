/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:46:38 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/13 17:39:30 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	exec_error(char **cmd_args)
{
	write(2, cmd_args[0], ft_strlen(cmd_args[0]));
	write(2, ": command not found.\n", 27);
	return (1);
}

char	**path_splitter(char *envp_path)
{
	char	**split_paths;
	int		i;
	int		j;

	split_paths = ft_split_paths(envp_path, ':');
	i = 0;
	j = 0;
	return (split_paths);
}

char	**cmd_parsing(char **envp)
{
	int		i;
	char	*envp_path;
	char	**split_paths;

	i = 0;
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

int	cmd_exec(char *argv, char **envp)
{
	int		i;
	int		exec;
	char	**split_paths;
	char	**cmd_args;
	char	*cmd;

	i = 0;
	exec = 0;
	split_paths = cmd_parsing(envp);
	cmd_args = ft_split(argv, ' ');
	while (split_paths[i])
	{
		cmd = ft_strjoin(split_paths[i], cmd_args[0]);
		if (access(cmd, X_OK) == 0)
		{
			execve(cmd, cmd_args, envp);
			exec = 1;
			break ;
		}
		i++;
		free(cmd);
	}
	if (exec == 0)
		return (exec_error(cmd_args));
	return (0);
}
