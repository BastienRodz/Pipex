/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:33:08 by barodrig          #+#    #+#             */
/*   Updated: 2021/01/18 14:21:24 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tempdst;
	unsigned char	*tempsrc;

	if (!src && !dst)
		return (NULL);
	tempdst = (unsigned char *)dst;
	tempsrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		tempdst[i] = tempsrc[i];
		if (tempdst[i] == (unsigned char)c)
			return ((void *)(dst + i + 1));
		i++;
	}
	return (NULL);
}
