/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:37:28 by barodrig          #+#    #+#             */
/*   Updated: 2021/11/04 14:01:35 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*path_finder(char **envp)
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

char	**get_path(char **envp)
{
	char	*path;
	char	**paths;

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

void	define_pipe_position(t_global *g)
{
	if (g->cmd_nbr == 2)
	{
		g->pipe_before = 0;
		g->pipe_after = 1;
	}
	else
	{
		g->pipe_before = 1;
		g->pipe_after = 1;
	}
	return ;
}

void	launch_pipex(t_global *g)
{
	int	i;
	int	pid;

	g->status = 0;
	i = 0;
	pid = 1;
	while (++i < g->ac - 3 && pid != 0)
		pid = fork();
	if (pid == -1)
		_error(3, g->path);
	else if (pid > 0)
	{
		waitpid(pid, &g->status, 0);
		parent_process(g, g->av);
	}
	else
	{
		g->cmd_nbr = i;
		define_pipe_position(g);
		child_process(g, g->av);
	}
	return ;
}

int	main(int ac, char **av, char **envp)
{
	t_global	g;

	if (ac < 5)
		_error(0, NULL);
	g.path = get_path(envp);
	if (!g.path)
		_error(1, NULL);
	g.file1 = av[1];
	g.file2 = av[ac];
	g.ac = ac;
	g.av = av;
	g.envp = envp;
	if (pipe(g._pipe[1]) == -1)
		_error(3, g.path);
	launch_pipex(&g);
	return (0);
}
