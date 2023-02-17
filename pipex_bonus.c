/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:00 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/17 13:49:21 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
** Each child process will read from the read end of the previous pipe, 
** and write to the write end of the next pipe (unless it's the first command,
** which reads from the input file or the last command, which writes 
** to the outfile).
*/

void	child_process(int i, t_pipex table, char **argv, char **envp)
{
	if (dup2(table.prev_pipe_fd[0], STDIN_FILENO) == -1)
		print_error("Child in");
	if (i == table.total_cmds - 1)
	{
		if (dup2(table.outfile_fd, STDOUT_FILENO) == -1)
			print_error("Child out");
	}
	else
	{
		if (dup2(table.pipe_fd[1], STDOUT_FILENO) == -1)
			print_error("Child out");
	}
	close(table.pipe_fd[0]);
	close(table.pipe_fd[1]);
	close(table.prev_pipe_fd[0]);
	if (i > 0)
		close(table.prev_pipe_fd[1]);
	if (cmd_exec(argv[i + 2 + table.has_heredoc], envp) == 1)
		exit(1);
}

/*
** The parent process will pass the fds of the current pipe
** (after command execution) to the ones of the previous pipe, 
** allowing the create_pipe function's loop to continue working. 
*/

t_pipex	parent_process(int i, t_pipex table)
{
	close(table.prev_pipe_fd[0]);
	if (i > 0)
		close(table.prev_pipe_fd[1]);
	table.prev_pipe_fd[0] = table.pipe_fd[0];
	table.prev_pipe_fd[1] = table.pipe_fd[1];
	return (table);
}

/*
** Recursively creates pipes, and forks the parent process to create
** a child per command. Closes any opened fds after command execution,
** to prevent zombie processes. It is important to have the fds of 
** the previous pipe, as they will be used to store the fds of 
** the current pipe after execution.
*/

void	create_pipe(t_pipex table, char **argv, char **envp)
{
	int		i;
	pid_t	child_pid;

	table.prev_pipe_fd[0] = table.infile_fd;
	table.prev_pipe_fd[1] = -1;
	i = 0;
	while (i < table.total_cmds)
	{
		if (pipe(table.pipe_fd) == -1)
			print_error("Pipe");
		child_pid = fork();
		if (child_pid == -1)
			print_error("Fork");
		else if (child_pid == 0)
			child_process(i, table, argv, envp);
		else if (child_pid > 0)
			table = parent_process(i, table);
		i++;
	}
	waitpid(child_pid, NULL, 0);
	close(table.prev_pipe_fd[0]);
	if (table.total_cmds > 1)
		close(table.prev_pipe_fd[1]);
	if (table.has_heredoc == 1)
		unlink("tmp_file");
}

/*
** To emulate the behaviour of a here_doc, a temporary file is created
** as input, and the contents of stdin are printed in it line by line, until
** the limiter is reached. Get_next_line is used to parse each line at a time
*/

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

/*
** Basic argument validation, checking for the correct number of args
** and if the specified files are able to be opened. The outfile is created
** if it doesn't exist, but the infile needs to be an already existing file, 
** unless here_doc has been specificed as first argument.
*/

int	main(int argc, char **argv, char **envp)
{
	t_pipex	table;

	table.has_heredoc = 0;
	if (argc < 5)
		init_error();
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		table.infile_fd = heredoc_parse(argv[2]);
		table.outfile_fd = \
			open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 00666);
		table.has_heredoc = 1;
	}
	else
	{
		table.infile_fd = open(argv[1], O_RDONLY);
		if (table.infile_fd == -1)
			print_error(argv[1]);
		table.outfile_fd = \
			open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 00666);
		if (table.outfile_fd == -1)
			print_error(argv[argc - 1]);
	}
	table.total_cmds = argc - table.has_heredoc - 3;
	create_pipe(table, argv, envp);
}
