/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:00 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/17 13:49:33 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** The first created child, using dup2 it will replace stdin as input for
** the first command, and will output to the write end of the pipe (pipe_fd[1]).
*/

void	child_process1(int infile_fd, int *pipe_fd, char **argv, char **envp)
{
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		print_error("Child 1");
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		print_error("Child 1");
	close(pipe_fd[0]);
	if (cmd_exec(argv[2], envp) == 1)
		exit(1);
}

/*
** The second created child, using dup2 it will read from the read end of 
** the pipe (pipe_fd[0]) as input for the second command, and will output 
** to the outfile (replacing stdout due to the use of dup2).
*/

void	child_process2(int outfile_fd, int *pipe_fd, char **argv, char **envp)
{
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		print_error("Child 2");
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		print_error("Child 2");
	close(pipe_fd[1]);
	cmd_exec(argv[3], envp);
}

/*
** Creates a pipe, and forks the parent process twice to create
** two child processes. Closes any opened fds after command execution,
** to prevent zombie processes.
*/

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

/*
** Basic argument validation, checking for the correct number of args
** and if the specified files are able to be opened. The outfile is created
** if it doesn't exist, but the infile needs to be an already existing file.
*/

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
