/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:00 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/15 04:44:44 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*void	child_process(int infile_fd, int *pipe_fd, char **argv, char **envp)
{
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		perror("Dup stdin child");
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror("Dup stdout child");
	close(pipe_fd[0]);
	if (cmd_exec(argv[2], envp) == 1)
		exit(1);
}*/

void	create_pipe(int infile_fd, int outfile_fd, char **argv, char **envp, int total_cmds)
{
	int		pipe_fd[2];
	int		prev_pipe_fd[2];
	int		i;
	pid_t	child_pid;

	prev_pipe_fd[0] = infile_fd;
	prev_pipe_fd[1] = -1;
	i = 0;
	while (i < total_cmds)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("Pipe");
			exit(1);
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Fork");
			exit(1);
		}
		else if (child_pid == 0)
		{
			//child_process(infile_fd, pipe_fd, argv, envp);
			dup2(prev_pipe_fd[0], STDIN_FILENO);
			if (i == total_cmds - 1)
				dup2(outfile_fd, STDOUT_FILENO);
			else
				dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			close(prev_pipe_fd[0]);
			if (i > 0)
				close(prev_pipe_fd[1]);
			if (cmd_exec(argv[i + 2], envp) == 1)
				exit(1);
		}
		else if (child_pid > 0)
		{
			close(prev_pipe_fd[0]);
			if (i > 0)
				close(prev_pipe_fd[1]);
			prev_pipe_fd[0] = pipe_fd[0];
			prev_pipe_fd[1] = pipe_fd[1];
		}
		i++;
	}
	waitpid(child_pid, NULL, 0);
	close(prev_pipe_fd[0]);
	if (total_cmds > 1)
		close(prev_pipe_fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile_fd;
	int		outfile_fd;
	int		total_cmds;

	if (argc < 5)
	{
		write(2, "Error: invalid number of arguments.\n", 37);
		exit(1);
	}
	total_cmds = argc - 3;
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	outfile_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 00666);
	if (outfile_fd == -1)
	{
		perror(argv[argc - 1]);
		exit(1);
	}
	create_pipe(infile_fd, outfile_fd, argv, envp, total_cmds);
}
