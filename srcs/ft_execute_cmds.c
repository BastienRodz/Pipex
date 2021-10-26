/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:16:47 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/26 15:42:37 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*testpath(char *path, char *cmd)
{
	char	*pathname;

	pathname = (char *)calloc(sizeof(char), (ft_strlen(path) + ft_strlen(cmd) + 2));
	ft_strcat(path, pathname);
	ft_strcat("/", pathname);
	ft_strcat(cmd, pathname);
	return (pathname);
}

void	find_cmd_path(char **cmd, char **envp, char **path, int _pipe[2][2])
{
	char	*pathname;
	int		i;

	i = -1;
	pathname = NULL;
	while (path[++i] && pathname == NULL)
	{
		pathname = testpath(path[i], cmd[0]);
		if (access(pathname, F_OK) == 0)
			break;
		free(pathname);
		pathname = NULL;
	}
	free(cmd[0]);
	// TO CHANGE
	cmd[0] = pathname;
	if (pathname == NULL)
		_error_cmd(cmd, _pipe);
	else
	{
		execve(pathname, cmd, envp);
		exit(0);
	}
	return ;
}

void	child_process(char **av, char **envp, char **path, int _pipe[2][2])
{
	char	**builtcmd;

	_pipe[0][0] = open(av[1], O_RDONLY, 0777);
	if (_pipe[0][0] == -1)
	{
		printf("ERROR TO HANDLE WITH THE MANAGER FOR FD[0]\n");
		exit(-1);
	}
	builtcmd = NULL;
	builtcmd = ft_split(av[2], ' ');
	dup2(_pipe[1][1], STDOUT_FILENO);
	dup2(_pipe[0][0], STDIN_FILENO);
	close(_pipe[1][0]);
	find_cmd_path(builtcmd, envp, path, _pipe);
	return ;
}

void	parent_process(char **av, char **envp, char **path, int _pipe[2][2])
{
	char	**builtcmd;

	_pipe[0][1] = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 00700);
	if (_pipe[0][1] == -1)
	{
		printf("ERROR TO HANDLE WITH THE MANAGER FOR FD[1]\n");
		exit(-1);
	}
	builtcmd = NULL;
	builtcmd = ft_split(av[3], ' ');
	close(_pipe[1][1]);
	dup2(_pipe[1][0], STDIN_FILENO);
	dup2(_pipe[0][1], STDOUT_FILENO);
	close(_pipe[1][1]);
	find_cmd_path(builtcmd, envp, path, _pipe);
	return ;
}
