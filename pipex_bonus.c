/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:00 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/13 19:33:51 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	create_pipe(int infile_fd, int outfile_fd, char **argv, char **envp, int total_pipe_fds)
{
	int		pipe_fd[2];
	pid_t	fork_pid1;
	pid_t	fork_pid2;

	//while (i < )
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

int	main(int argc, char **argv, char **envp)
{
	int		infile_fd;
	int		outfile_fd;
	int		total_cmds;
	int		total_pipe_fds;

	if (argc < 5)
	{
		write(2, "Error: invalid number of arguments.\n", 37);
		exit(1);
	}
	total_cmds = argc - 3;
	total_pipe_fds = 2 * (total_cmds - 1);
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
	create_pipe(infile_fd, outfile_fd, argv, envp, total_pipe_fds);
}