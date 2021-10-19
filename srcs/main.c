/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:18:24 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/15 18:24:54 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av)
{
	int pid;
	int fd[2];

	if (ac != 5)
	{
		write(1, "You need 4 arguments to make this program run.\n", 49);
		return (-1);
	}

	return (0);
}
