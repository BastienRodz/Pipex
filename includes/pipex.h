/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:36:00 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/26 15:37:01 by barodrig         ###   ########.fr       */
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

/**
** ERROR MANAGER
**/
void	_error(int i);
void	ft_to_break_free(char **str);
void	_error_cmd(char **cmd, int _pipe[2][2]);

/**
** EXECUTION
**/
void	parent_process(char **av, char **envp, char **path, int _pipe[2][2]);
void	child_process(char **av, char **envp, char **path, int _pipe[2][2]);

#endif
