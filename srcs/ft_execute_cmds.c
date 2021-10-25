/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:16:47 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/25 16:31:04 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*testpath(char *path, char *cmd)
{
	char	*pathname;

	pathname = (char *)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(cmd) + 2));
	ft_strcat(path, pathname);
	ft_strcat("/", pathname);
	ft_strcat(cmd, pathname);
	return (pathname);
}

void	find_cmd_path(char **cmd, char **envp, char **path, int _pipe[2][2])
{
	char	*pathname;
	int		i;

	i = 0;
	pathname = NULL;
	while (path[i] && pathname == NULL)
	{
		pathname = testpath(path[i], cmd[0]);
		if (access(pathname, F_OK) == 0)
			break;
		free(pathname);
		pathname = NULL;
		i++;
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

void	child_process(char *cmd, char **envp, char **path, int _pipe[2][2])
{
	char	**builtcmd;

	builtcmd = NULL;
	builtcmd = ft_split(cmd, ' ');
	close(_pipe[1][0]);
	dup2(_pipe[1][1], 1);
	dup2(_pipe[0][0], 0);
	close(_pipe[1][1]);
	find_cmd_path(builtcmd, envp, path, _pipe);
	return ;
}

void	parent_process(char *cmd, char **envp, char **path, int _pipe[2][2])
{
	char	**builtcmd;

	builtcmd = NULL;
	builtcmd = ft_split(cmd, ' ');
	close(_pipe[1][1]);
	dup2(_pipe[1][0], 0);
	dup2(_pipe[0][1], 1);
	close(_pipe[1][0]);
	find_cmd_path(builtcmd, envp, path, _pipe);
	return ;
}
