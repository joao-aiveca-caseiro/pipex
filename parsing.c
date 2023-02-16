/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:46:38 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/16 01:46:59 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_error(char **cmd_args)
{
	write(2, cmd_args[0], ft_strlen(cmd_args[0]));
	write(2, ": command not found.\n", 22);
	return (1);
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
			envp_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	split_paths = ft_split_paths(envp_path, ':');
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
