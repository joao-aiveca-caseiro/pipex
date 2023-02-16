/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:32 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/16 14:21:43 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int	infile_fd;
	int	outfile_fd;
	int	total_cmds;
	int	has_heredoc;
	int	prev_pipe_fd[2];
	int	pipe_fd[2];
}		t_pipex;

int		cmd_exec(char *argv, char **envp);
char	**cmd_parsing(char **envp);
int		exec_error(char **cmd_args);
void	create_pipe(t_pipex table, char **argv, char **envp);
void	child_process(int i, t_pipex table, char **argv, char **envp);
t_pipex	parent_process(int i, t_pipex table);
void	print_error(char *msg);
void	init_error(void);

#endif
