/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:11:51 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/15 16:56:50 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;

	size = ft_strlen((char *)s);
	if ((char)c == 0)
		return ((char *)s + size);
	while (size--)
	{
		if (*(s + size) == c)
			return ((char *)(s + size));
	}
	return (0);
}
