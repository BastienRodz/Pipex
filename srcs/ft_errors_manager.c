/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:46:10 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/26 14:45:19 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_to_break_free(char **str)
{
	int	i;

	i = 0;
	while (str[i++])
		free(str[i]);
	free(str);
	return ;
}
void	_error_cmd(char **cmd, int _pipe[2][2])
{
	ft_to_break_free(cmd);
	close(_pipe[0][0]);
	close(_pipe[0][1]);
	exit(0);
}

void	_error(int i)
{
	if (i == 0)
	{
		write(1, "You need 4 arguments to make this program run.\n", 47);
		exit(0);
	}
	if	(i == 1)
	{
		write(1, "ERROR WHILE GETTING CMD PATHS IN ENVIRONMENT VARIABLES.\n", 56);
		exit(0);
	}
}
