/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:18:24 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/25 16:28:58 by barodrig         ###   ########.fr       */
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
	files_opener(_pipe, av);
	if (pid > 0)
		parent_process(av[3], envp, path, _pipe);
	else
		child_process(av[2], envp, path, _pipe);
	return (0);
}
