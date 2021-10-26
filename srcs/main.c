/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:18:24 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/26 15:44:20 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char*	path_finder(char **envp)
{
	int		i;
	int		j;
	char	*path;
	char	*str;

	str = "PATH=";
	path = NULL;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == str[j])
			j++;
		if (!str[j])
		{
			path = envp[i];
			return (path);
		}
		i++;
	}
	return (NULL);
}

char**	get_path(char **envp)
{
	char *path;
	char **paths;

	path = path_finder(envp);
	if (*path)
	{
		path = path + 5;
		paths = ft_split(path, ':');
		return (paths);
	}
	else
		return (NULL);

}

int	main(int ac, char **av, char **envp)
{
	char	**path;
	int		pid;
	int		_pipe[2][2];
	int		status;

	status = 0;
	path = get_path(envp);
	if (ac != 5)
		_error(0);
	(void)av;
	if (!path)
		_error(1);
	if (pipe(_pipe[1]) == -1)
	{
		ft_to_break_free(path);
		_error(2);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_to_break_free(path);
		_error(3);
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		parent_process(av, envp, path, _pipe);
	}
	else
		child_process(av, envp, path, _pipe);
	return (0);
}
