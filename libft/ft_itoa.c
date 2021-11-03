/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:09:18 by barodrig          #+#    #+#             */
/*   Updated: 2021/10/15 17:10:55 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

long int	ft_change_sign(long int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

int	ft_sign(int n)
{
	if (n < 0)
		return (-1);
	else
		return (1);
}

int	ft_len(long int nbr)
{
	int	len;

	if (nbr <= 0)
		len = 1;
	else
		len = 0;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;

	sign = ft_sign(n);
	len = ft_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = '0' + ft_change_sign(n % 10);
		n = n / 10;
		len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
