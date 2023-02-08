/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:32 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/08 16:15:46 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

void	cmd_exec(char *argv, char **envp);
char	**cmd_parsing(char **envp);
char	**path_splitter(char *envp_path);
void	create_pipe(int infile_fd, int outfile_fd, char **argv, char **envp);
void	parent_process(int outfile_fd, int *pipe_fd, char **argv, char **envp);
void	child_process(int infile_fd, int *pipe_fd, char **argv, char **envp);

#endif
