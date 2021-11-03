/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:47:18 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/15 16:58:14 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	long int		size;

	size = dstsize;
	i = ft_strlen(dst);
	j = 0;
	if (size < i)
		return (ft_strlen(src) + size);
	while (src[j] && (i + j) < (size - 1))
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (ft_strlen(src) + i);
}
