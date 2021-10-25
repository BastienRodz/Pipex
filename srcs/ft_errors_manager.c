/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:46:10 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/25 13:53:24 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	_error(int i)
{
	if (i == 0)
	{
		write(1, "You need 4 arguments to make this program run.\n", 47);
		exit(0);
	}
	if	(i == 1)
	{
		write(1, "ERROR WHILE GETTING CMD PATHS IN ENVIRONMENT VARIABLES.\n", 56);
		exit(0);
	}
}
