/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:46:10 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/27 11:15:43 by barodrig         ###   ########.fr       */
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

void	_error_next(int i)
{
	if (i == 4)
	{
		write(2, "output: No such file or directory\n", 34);
		exit(0);
	}
	else if (i == 5)
	{
		write(2, "input: No such file or directory\n", 33);
		exit(0);
	}
	else if (i == 6)
	{
		write(2, "Impossible to find one of the command.\n", 39);
		exit(0);
	}
	else
		return ;
}

void	_error(int i)
{
	if (i == 0)
	{
		write(2, "You need 4 arguments to make this program run.\n", 47);
		exit(0);
	}
	else if	(i == 1)
	{
		write(2, "ERROR WHILE GETTING CMD PATHS IN ENVIRONMENT VARIABLES.\n", 56);
		exit(0);
	}
	else if	(i == 2)
	{
		write(2, "ONE OF THE ARGUMENT IS EMPTY.\n", 30);
		exit(0);
	}
	else if	(i == 3)
	{
		write(2, "ERROR WHILE CREATING PIPE.\n", 27);
		exit(0);
	}
	else
		_error_next(i);
	return ;
}
