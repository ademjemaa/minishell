/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 09:35:22 by abarbour          #+#    #+#             */
/*   Updated: 2019/11/11 10:46:54 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size(int n)
{
	if (n / 10)
		return (1 + size(n / 10));
	return (1);
}

static void	convert(char *str, int n, int i)
{
	if (n / 10)
		convert(str, n / 10, i - 1);
	str[i] = n % 10 + 48;
}

char		*ft_itoa(int n)
{
	char	*str;
	int		s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	s = size(n);
	if (n < 0)
		s++;
	if (!(str = (char *)malloc(s + 1)))
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		convert(str, -n, s - 1);
	}
	else
		convert(str, n, s - 1);
	str[s] = '\0';
	return (str);
}
