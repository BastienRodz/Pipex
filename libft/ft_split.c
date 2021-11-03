/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:39:06 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/15 17:02:41 by barodrig         ###   ########.fr       */
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
		if (src[i] != charset && (src[i + 1] == charset || src[i + 1] == '\0'))
			words++;
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

void	*ft_leak(char **split, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char	**ft_write_words(char **split, char const *src, char charset, int words)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < words)
	{
		while (*src == charset)
			src++;
		len = ft_words_len(src, charset);
		split[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!(split[i]))
			return (ft_leak(split, i));
		j = 0;
		while (j < len)
			split[i][j++] = *src++;
		split[i][j] = '\0';
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char const *src, char charset)
{
	char	**split;
	int		words;

	if (!src)
		return (NULL);
	words = ft_count_words(src, charset);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!(split))
		return (NULL);
	split = ft_write_words(split, src, charset, words);
	return (split);
}
