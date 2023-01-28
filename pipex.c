/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:00 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/01/28 16:00:24 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_parsing_pipex(char **envp)
{
	char *envp_path;

	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	infile_fd;
	int	outfile_fd;
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}

	if (argc > 4)
	{
		infile_fd = open(argv[1], O_RDWR);
		if (infile_fd == -1)
			perror("Error");
		outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT);
	}
}
