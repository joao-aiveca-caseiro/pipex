/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:00 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/16 03:06:11 by jaiveca-         ###   ########.fr       */
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

void	create_pipe(int infile_fd, int outfile_fd, char **argv, char **envp, int total_cmds, int has_heredoc)
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
			if (cmd_exec(argv[i + 2 + has_heredoc], envp) == 1)
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

int	heredoc_parse(char *limiter)
{
	int		infile_fd;
	char	*input;

	infile_fd = open("tmp_file", O_WRONLY | O_CREAT, 00666);
	limiter = ft_strjoin(limiter, "\n");
	input = ft_calloc(1, 1);
	while (ft_strncmp(input, limiter, ft_strlen(limiter)) != 0)
	{
		free(input);
		input = get_next_line(0);
		if (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(infile_fd, input, ft_strlen(input));
	}
	free(input);
	free(limiter);
	close(infile_fd);
	infile_fd = open("tmp_file", O_RDONLY);
	return (infile_fd);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile_fd;
	int		outfile_fd;
	int		total_cmds;
	int		has_heredoc;

	has_heredoc = 0;
	if (argc < 5)
	{
		write(2, "Error: invalid number of arguments.\n", 37);
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		infile_fd = heredoc_parse(argv[2]);
		outfile_fd = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 00666);
		has_heredoc = 1;
	}
	else
	{
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
	}
	total_cmds = argc - has_heredoc - 3;
	create_pipe(infile_fd, outfile_fd, argv, envp, total_cmds, has_heredoc);
}
