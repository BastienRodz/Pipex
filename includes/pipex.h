/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:36:00 by barodrig          #+#    #+#             */
/*   Updated: 2021/11/02 16:15:03 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include "./libft.h"

typedef struct s_global
{
	char			*file1;
	char			*file2;
	int				ac;
	char			**av;
	int				pipe_before;
	int				pipe_after;
	int				cmd_nbr;
	int				_pipe[2][2];
	char			**envp;
	char			**path;
	int				status;
	int				here_doc;
	char			*LIMITER;
}					t_global;

/**
** ERROR MANAGER
**/
void	_error(int i, char	**to_free);
void	ft_to_break_free(char **str);
void	_error_cmd(char **cmd, int _pipe[2][2]);

/**
** EXECUTION
**/
void	parent_process(t_global *g);
void	child_process(t_global *g);

/**
** BONUS
**/
void	parent_process_bonus(t_global *g, char **av);
void	child_process_bonus(t_global *g, char **av);

#endif
