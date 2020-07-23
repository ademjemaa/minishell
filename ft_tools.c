/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 00:11:06 by adjemaa           #+#    #+#             */
/*   Updated: 2020/06/17 00:11:22 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_cal(char	*line, int *i)
{
	char	c;

	c = line[*i];
	*i = *i + 1;
	while (line[*i] && line[*i] != c)
	{
		if (line[*i] == '\\' && c != '\'')
			*i = *i + 1;
		*i = *i + 1;
	}
	*i = *i + 1;
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
