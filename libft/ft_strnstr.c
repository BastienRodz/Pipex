/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:52:37 by barodrig          #+#    #+#             */
/*   Updated: 2021/01/18 10:46:55 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *hay, const char *ndl, size_t len)
{
	unsigned int		i;
	unsigned int		j;

	if (ndl[0] == '\0')
		return ((char *)hay);
	i = 0;
	while (hay[i] && i < len)
	{
		j = 0;
		if (hay[i] == ndl[j])
		{
			while (i + j < len && hay[i + j] == ndl[j])
			{
				j++;
				if (!ndl[j])
					return ((char *)&hay[i]);
			}
		}
		i++;
	}
	return (0);
}
