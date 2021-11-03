/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:16:47 by barodrig          #+#    #+#             */
/*   Updated: 2021/11/03 13:35:07 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
** As its name says "testpath_builder" will create a path to try to access our command.
**/

char	*testpath_builder(t_global *g, char *cmd, int i)
{
	char	*pathname;

	if (cmd == NULL)
	{
		if (cmd)
			free(cmd);
		_error(2, g->path);
	}
	pathname = (char *)calloc(sizeof(char), (ft_strlen(g->path[i]) + ft_strlen(cmd) + 2));
	ft_strcat(g->path[i], pathname);
	ft_strcat("/", pathname);
	ft_strcat(cmd, pathname);
	return (pathname);
}

/**
** "find_cmd_path" will call "testpath_builder" and try to access() the test path given by it.
**	In case of failure it will try another test path.
**	In case of success it will execve() the cmd path and its flags if there are some.
**/

void	find_cmd_path(char **builtcmd, t_global *g)
{
	char	*pathname;
	int		i;

	i = -1;
	pathname = NULL;
	while (g->path[++i] && pathname == NULL)
	{
		pathname = testpath_builder(g, builtcmd[0], i);
		if (access(pathname, F_OK) == 0)
			break;
		free(pathname);
		pathname = NULL;
	}
	if (pathname == NULL)
		_error_cmd(builtcmd, pathname, g);
	free(builtcmd[0]);
	builtcmd[0] = pathname;
	execve(pathname, builtcmd, g->envp);
	ft_to_break_free(g->path);
	ft_to_break_free(builtcmd);
	exit(0);
	return ;
}

/**
** "child_process" is the process created by the fork. It will take as STDIN the file1 given in av[1].
** Then it will split av[2] to separate the name of cmd1 from its flags if there are sonme.
** The function will change the _pipe[1][1] (pipe writing extremity) in STDOUT to allow it to recover the output of cmd1.
** Finally it will close the reading part of the _pipe and launch the cmd execution by calling find_cmd_path().
**/

void	child_process(t_global *g, char **av)
{
	char	**builtcmd;
	char	*error;

	error = NULL;
	builtcmd = NULL;
	if (g->pipe_before == 0)
	{
		g->_pipe[0][0] = open(av[1], O_RDONLY, 0777);
		if (g->_pipe[0][0] == -1)
		{
			ft_to_break_free(g->path);
			error = strerror(errno);
			write(2, "Error: ", 7);
			write(2, error, ft_strlen(error));
			write(2, "\n", 1);
			exit(1);
		}
		dup2(g->_pipe[1][1], STDOUT_FILENO);
		dup2(g->_pipe[0][0], STDIN_FILENO);
		close(g->_pipe[1][0]);
	}
	else
	{
		dup2(g->_pipe[1][0], STDIN_FILENO);
		dup2(g->_pipe[1][1], STDOUT_FILENO);
		//close(_pipe[1][0]);
	}
	builtcmd = ft_split(av[g->cmd_nbr], ' ');
	find_cmd_path(builtcmd, g);
	return ;
}

/**
** "parent_process" is the main process of our program. It will change as STDIN the _pipe[1][0] (pipe reading extremity).
** Then it will split av[3] to separate the name of cmd0 from its flags if there are sonme.
** The function will change the fd[1] in STDOUT to allow it to recover the output of cmd2 (fd[1] is file2 here).
** Finally it will close the writing part of the _pipe and launch the cmd execution by calling find_cmd_path().
**/

void	parent_process(t_global *g, char **av)
{
	char	**builtcmd;
	char	*error;

	error = NULL;
	builtcmd = NULL;
	g->_pipe[0][1] = open(av[g->ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 00777);
	if (g->_pipe[0][1] == -1)
	{
		ft_to_break_free(g->path);
		error = strerror(errno);
		write(2, "Error: ", 7);
		write(2, error, ft_strlen(error));
		write(2, "\n", 1);
		exit(1);
	}
	builtcmd = ft_split(av[g->ac - 2], ' ');
	dup2(g->_pipe[1][0], STDIN_FILENO);
	dup2(g->_pipe[0][1], STDOUT_FILENO);
	close(g->_pipe[1][1]);
	find_cmd_path(builtcmd, g);
	return ;
}
