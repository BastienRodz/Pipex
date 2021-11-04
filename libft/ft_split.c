/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:39:06 by barodrig          #+#    #+#             */
/*   Updated: 2021/11/04 11:33:18 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_count_words(char const *src, char charset)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (src[i])
	{
		while (src[i] == charset)
			i++;
		if (src[i] != charset && src[i])
			words++;
		while (src[i] != charset && src[i])
			i++;
	}
	return (words);
}

int	ft_words_len(const char *src, char charset)
{
	int	len;

	len = 0;
	while (src[len] != charset && src[len] != '\0')
		len++;
	return (len);
}

void	*ft_leak(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (NULL);
}

char	**ft_split(char const *src, char charset)
{
	char	**split;
	int		words;
	int		len;
	int		i;

	i = -1;
	if (!src)
		return (NULL);
	words = ft_count_words(src, charset);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!(split))
		return (NULL);
	while (words-- && ++i > -2)
	{
		while (*src == charset && *src)
			src++;
		len = ft_words_len(src, charset);
		split[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!(split[i]))
			return (ft_leak(split));
		ft_strlcpy(split[i], src, len + 1);
		src = src + len;
	}
	split[i + 1] = NULL;
	return (split);
}
