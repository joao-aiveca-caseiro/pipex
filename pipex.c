/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:00 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/16 14:36:11 by jaiveca-         ###   ########.fr       */
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
	if (cmd_exec(argv[2], envp) == 1)
		exit(1);
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
	pid_t	child1_pid;
	pid_t	child2_pid;

	child2_pid = 0;
	if (pipe(pipe_fd) == -1)
		perror("Pipe");
	child1_pid = fork();
	if (child1_pid == -1)
		perror("Fork");
	else if (child1_pid == 0)
		child_process1(infile_fd, pipe_fd, argv, envp);
	else if (child1_pid > 0)
	{
		child2_pid = fork();
		if (child2_pid == -1)
			perror("Fork");
		else if (child2_pid == 0)
			child_process2(outfile_fd, pipe_fd, argv, envp);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(child2_pid, NULL, 0);
	close(infile_fd);
	close(outfile_fd);
}

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
	create_pipe(infile_fd, outfile_fd, argv, envp);
}
