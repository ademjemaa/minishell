/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:47:01 by abarbour          #+#    #+#             */
/*   Updated: 2019/11/13 13:35:46 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char  *s1, char  *set)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*x;

	if (!s1)
		return (NULL);
	x = (char *)s1;
	while (ft_strchr(set, (int)x[0]) && x[0])
		x = x + 1;
	if (x[0] == '\0')
		return (ft_strdup(""));
	i = ft_strlen(x) - 1;
	while (ft_strchr(set, (int)x[i]))
		i--;
	if (!(str = (char *)malloc(i + 2)))
		return (NULL);
	j = 0;
	while (j < i + 1)
	{
		str[j] = x[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
