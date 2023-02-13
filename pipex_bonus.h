/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:32 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/13 18:56:44 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

int		cmd_exec(char *argv, char **envp);
char	**cmd_parsing(char **envp);
char	**path_splitter(char *envp_path);
int		exec_error(char **cmd_args);
void	create_pipe(int infile_fd, int outfile_fd, char **argv, char **envp, int total_pipe_fds);
void	child_process1(int outfile_fd, int *pipe_fd, char **argv, char **envp);
void	child_process2(int infile_fd, int *pipe_fd, char **argv, char **envp);

#endif
