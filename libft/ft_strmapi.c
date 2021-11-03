/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:48:52 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/15 16:57:42 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char	*map;
	int		i;
	int		len;

	if (!str || !f)
		return (NULL);
	i = 0;
	map = NULL;
	len = ft_strlen((char *)str);
	map = (char *)malloc(sizeof(char) * (len + 1));
	if (!(map))
		return (NULL);
	while (i < len)
	{
		map[i] = f(i, str[i]);
		i++;
	}
	map[i] = '\0';
	return (map);
}
