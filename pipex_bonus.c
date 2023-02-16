/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:00 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/16 14:49:49 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(int i, t_pipex table, char **argv, char **envp)
{
	dup2(table.prev_pipe_fd[0], STDIN_FILENO);
	if (i == table.total_cmds - 1)
		dup2(table.outfile_fd, STDOUT_FILENO);
	else
		dup2(table.pipe_fd[1], STDOUT_FILENO);
	close(table.pipe_fd[0]);
	close(table.pipe_fd[1]);
	close(table.prev_pipe_fd[0]);
	if (i > 0)
		close(table.prev_pipe_fd[1]);
	if (cmd_exec(argv[i + 2 + table.has_heredoc], envp) == 1)
		exit(1);
}

t_pipex	parent_process(int i, t_pipex table)
{
	close(table.prev_pipe_fd[0]);
	if (i > 0)
		close(table.prev_pipe_fd[1]);
	table.prev_pipe_fd[0] = table.pipe_fd[0];
	table.prev_pipe_fd[1] = table.pipe_fd[1];
	return (table);
}

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
