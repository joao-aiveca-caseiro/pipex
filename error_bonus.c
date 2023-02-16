/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:32:33 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/02/16 14:48:56 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	exec_error(char **cmd_args)
{
	write(2, cmd_args[0], ft_strlen(cmd_args[0]));
	write(2, ": command not found.\n", 22);
	return (1);
}

void	print_error(char *msg)
{
	perror(msg);
	exit(1);
}

void	init_error(void)
{
	write(2, "Error: invalid number of arguments.\n", 37);
	exit(1);
}
