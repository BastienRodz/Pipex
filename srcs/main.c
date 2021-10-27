/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:18:24 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/27 11:23:39 by barodrig         ###   ########.fr       */
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

void	launch_pipex(char **path, int _pipe[2][2], char **envp, char **av)
{
	int	pid;
	int	status;

	status = 0;
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
}

/**
** "check_infile" will pre-check if the input file exist BEFORE forking.
** If I do not pre-check before forking the parent process will keep executing and create,
** the output file even if the input file does not exist. Which is not a good behaviour compare to bash.
**/

void	check_infile(char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
		_error(5);
	else
		close(fd);
	return ;
}

int	main(int ac, char **av, char **envp)
{
	char	**path;
	int		_pipe[2][2];

	check_infile(av);
	path = get_path(envp);
	if (ac != 5)
		_error(0);
	if (!path)
		_error(1);
	if (pipe(_pipe[1]) == -1)
	{
		ft_to_break_free(path);
		_error(3);
	}
	launch_pipex(path, _pipe, envp, av);
	return (0);
}
