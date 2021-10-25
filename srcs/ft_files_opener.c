/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files_opener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:33:11 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/25 15:59:45 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	files_opener(int fd[2][2], char **av)
{
	fd[0][0] = open(av[1], O_RDONLY);
	if (fd[0][0] == -1)
	{
		printf("ERROR TO HANDLE WITH THE MANAGER FOR FD[0]\n");
		exit(-1);
	}
	fd[0][1] = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 00700);
	if (fd[0][1] == -1)
	{
		printf("ERROR TO HANDLE WITH THE MANAGER FOR FD[1]\n");
		exit(-1);
	}
	return ;
}
