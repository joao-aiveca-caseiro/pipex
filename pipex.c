/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:00 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/11 04:10:41 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process1(int infile_fd, int *pipe_fd, char **argv, char **envp)
{
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		perror("Dup stdin child");
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror("Dup stdout child");
	close(pipe_fd[0]);
	cmd_exec(argv[2], envp);
/*
	exit before executing command if it doesnt exist
*/
}

void	child_process2(int outfile_fd, int *pipe_fd, char **argv, char **envp)
{
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror("Dup stdout child");
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		perror("Dup stdin child");
	close(pipe_fd[1]);
	cmd_exec(argv[3], envp);
}

void	create_pipe(int infile_fd, int outfile_fd, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	fork_pid1;
	pid_t	fork_pid2;

	if (pipe(pipe_fd) == -1)
		perror("Pipe");
	fork_pid1 = fork();
	if (fork_pid1 == -1)
		perror("Fork");
	else if (fork_pid1 == 0)
		child_process1(infile_fd, pipe_fd, argv, envp);
	fork_pid2 = fork();
	if (fork_pid2 == -1)
		perror("Fork");
	else if (fork_pid2 == 0)
		child_process2(outfile_fd, pipe_fd, argv, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(fork_pid1, NULL, 0);
	waitpid(fork_pid2, NULL, 0);
	close(infile_fd);
	close(outfile_fd);
}

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

void	cmd_exec(char *argv, char **envp)
{
	int		i;
	int		not_found;
	char	**split_paths;
	char	**cmd_args;
	char	*cmd;

	i = 0;
	not_found = 0;
	split_paths = cmd_parsing(envp);
	cmd_args = ft_split(argv, ' ');
	while (split_paths[i])
	{
		cmd = ft_strjoin(split_paths[i], cmd_args[0]);
		if (access(cmd, X_OK) == 0)
		{
			execve(cmd, cmd_args, envp);
			break ;
		}
		i++;
		if (not_found == i && split_paths[i] == NULL)
		{
			write(2, cmd_args[0], ft_strlen(cmd_args[0]));
			write(2, ": command not found.\n", 27);
			exit(1);
		}
		free(cmd);
	}
//	free(cmd_args);
//	free(split_paths);
}

/*void	cmd_exec(char *argv, char **envp)
{
	int		i;
	int		not_found;
	char	**split_paths;
	char	**cmd_args;
	char	*cmd;

	i = 0;
	not_found = 0;
	split_paths = cmd_parsing(envp);
	cmd_args = ft_split(argv, ' ');
	while (split_paths[i])
	{
		cmd = ft_strjoin(split_paths[i], cmd_args[0]);
		if (execve(cmd, cmd_args, envp) == -1)
			not_found++;
		else
			break ;
		i++;
		if (not_found == i && split_paths[i] == NULL)
		{
			ft_printf("%s: command not found\n", cmd_args[0]);
			exit(1);
		}
		free(cmd);
	}
//	free(cmd_args);
//	free(split_paths);
}*/

int	main(int argc, char **argv, char **envp)
{
	int		infile_fd;
	int		outfile_fd;
	if (argc != 5)
	{
		write(2, "Error: invalid number of arguments.\n", 37);
		exit(1);
	}
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
		ft_printf("Error: %s: %s\n", strerror(errno), argv[1]);
	outfile_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 00666);
	if (outfile_fd == -1)
		ft_printf("Error: %s: %s\n", strerror(errno), argv[argc - 1]);
	create_pipe(infile_fd, outfile_fd, argv, envp);
}
