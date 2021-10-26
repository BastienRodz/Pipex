/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:16:47 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/26 18:00:31 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
** As its name says "testpath_builder" will create a path to try to access our command.
**/

char	*testpath_builder(char *path, char *cmd)
{
	char	*pathname;

	if (cmd == NULL)
	{
		if (path)
			free(path);
		if (cmd)
			free(cmd);
		_error(2);
	}
	pathname = (char *)calloc(sizeof(char), (ft_strlen(path) + ft_strlen(cmd) + 2));
	ft_strcat(path, pathname);
	ft_strcat("/", pathname);
	ft_strcat(cmd, pathname);
	return (pathname);
}

/**
** "find_cmd_path" will call "testpath_builder" and try to access() the test path given by it.
**	In case of failure it will try another test path.
**	In case of success it will execve() the cmd path and its flags if there are some.
**/

void	find_cmd_path(char **builtcmd, char **envp, char **path, int _pipe[2][2])
{
	char	*pathname;
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	pathname = NULL;
	while (path[++i] && pathname == NULL)
	{
		pathname = testpath_builder(path[i], builtcmd[0]);
		if (access(pathname, F_OK) == 0)
		{
			flag = 1;
			break;
		}
		free(pathname);
		pathname = NULL;
	}
	if (!flag)
		_error(6);
	free(builtcmd[0]);
	builtcmd[0] = pathname;
	if (pathname == NULL)
		_error_cmd(builtcmd, _pipe);
	else
	{
		execve(pathname, builtcmd, envp);
		exit(0);
	}
	return ;
}

/**
** "child_process" is the process created by the fork. It will take as STDIN the file1 given in av[1].
** Then it will split av[2] to separate the name of cmd1 from its flags if there are sonme.
** The function will change the _pipe[1][1] (pipe writing extremity) in STDOUT to allow it to recover the output of cmd1.
** Finally it will close the reading part of the _pipe and launch the cmd execution by calling find_cmd_path().
**/

void	child_process(char **av, char **envp, char **path, int _pipe[2][2])
{
	char	**builtcmd;

	builtcmd = NULL;
	_pipe[0][0] = open(av[1], O_RDONLY, 0777);
	if (_pipe[0][0] == -1)
	{
		ft_to_break_free(path);
		_error(5);
	}
	builtcmd = ft_split(av[2], ' ');
	dup2(_pipe[1][1], STDOUT_FILENO);
	dup2(_pipe[0][0], STDIN_FILENO);
	close(_pipe[1][0]);
	find_cmd_path(builtcmd, envp, path, _pipe);
	return ;
}

/**
** "parent_process" is the main process of our program. It will change as STDIN the _pipe[1][0] (pipe reading extremity).
** Then it will split av[3] to separate the name of cmd0 from its flags if there are sonme.
** The function will change the fd[1] in STDOUT to allow it to recover the output of cmd2 (fd[1] is file2 here).
** Finally it will close the writing part of the _pipe and launch the cmd execution by calling find_cmd_path().
**/

void	parent_process(char **av, char **envp, char **path, int _pipe[2][2])
{
	char	**builtcmd;

	builtcmd = NULL;
	_pipe[0][1] = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 00700);
	if (_pipe[0][1] == -1)
	{
		ft_to_break_free(path);
		_error(4);
	}
	builtcmd = ft_split(av[3], ' ');
	dup2(_pipe[1][0], STDIN_FILENO);
	dup2(_pipe[0][1], STDOUT_FILENO);
	close(_pipe[1][1]);
	find_cmd_path(builtcmd, envp, path, _pipe);
	return ;
}
