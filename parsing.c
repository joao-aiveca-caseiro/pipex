/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:46:38 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/17 13:07:43 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Finds PATH in the list of environment variables (envp), then
** splits it into an array of possible command locations.
*/

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

/*
** Parses the command into a format readable by execve (path + CMD name
** as first argument), array of command arguments as the second argument).
** Checks using access if the command exists at any of the splitted paths
** of the previous function and is executable.
*/

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
