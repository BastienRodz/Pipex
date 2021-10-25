/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:18:24 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/25 13:49:47 by barodrig         ###   ########.fr       */
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
	//int		pid;
	//int		_pipe[2][2];

	path = get_path(envp);
	if (ac != 5)
		_error(0);
	(void)av;
	if (!path)
		_error(1);

	/* int _pipe[2][2];
	int p[2];
	read(p[0])
	write(p[1])
	bool _p_before;
	bool _p_after;

pipe(p);

	fork()
	{//enfant

		//if pipe after
		dup2(sortie cmd actuelle > entree cmd suivante)
		//if pipe before
		dup2(sortie cmd precedente > entree cmd actuelle)

		execve( "/bin/echo", char ** , env);
		//ls dans le pipe

	}
	{//parent
		//ls dans pipe
		//dup2 (entree cmd suivante, sortie commande actuelle)
	}*/


	return (0);
}
