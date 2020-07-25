/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 21:45:28 by adjemaa           #+#    #+#             */
/*   Updated: 2020/07/26 00:08:32 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		total(char const *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char			*ft_strjoinfree(char *s1, char *s2, int crit)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	s1 = s1 ? s1 : ft_strdup("");
	s2 = s2 ? s2 : ft_strdup("");
	if (!(str = malloc(total(s1) + total(s2) + 1)))
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i++] = s2[j];
	str[i] = '\0';
	if (crit == 1)
		free(s1);
	else if (crit == 2)
		free(s2);
	else
	{
		free(s1);
		free(s2);
	}
	return (str);
}
