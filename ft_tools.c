/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 00:11:06 by adjemaa           #+#    #+#             */
/*   Updated: 2020/07/23 22:38:54 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		arg_handler(char *str, char *tmp, int *i)
{
	while (str[*i] == '\\' && str[0] != '\'')
		backslash(str, tmp, i, 0);
	if ((str[*i] == '>' || str[*i] == '<') && !((str[0] == '\'') ||
		str[0] == '\"'))
		return (1);
	if (str[0] == '\'' || str[0] == '\"')
	{
		if (backslash(str, tmp, i, 1))
			return (1);
	}
	else if (str[*i] == ' ' || str[*i] == '\'' || str[*i] == '\"')
	{
		if (str[*i] == ' ')
			tmp[(*i)++] = ' ';
		return (1);
	}
	else
		tmp[*i] = str[*i];
	return (0);
}

int		backslash(char *str, char *tmp, int *i, int cond)
{
	char	c;

	c = str[0];
	if (cond == 0)
	{
		tmp[*i] = str[*i];
		*i = *i + 1;
		tmp[*i] = str[*i];
		*i = *i + 1;
	}
	else if (cond == 1)
	{
		if (c == str[*i] && *i != 0)
		{
			tmp[*i] = str[*i];
			*i = *i + 1;
			if (str[*i] == ' ')
				tmp[(*i)++] = ' ';
			return (1);
		}
		else
			tmp[*i] = str[*i];
	}
	return (0);
}

void	quotes_cal(char *line, int *i)
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

int		ft_strcmp(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
