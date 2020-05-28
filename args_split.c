/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 18:01:22 by adjemaa           #+#    #+#             */
/*   Updated: 2020/05/28 18:58:48 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	total_argus(char *line)
{
	int i;
	char c;
	int total;

	total = 1;
	i = 0;
	while (line[i])
	{
		while (line[i] == '\\')
			i = i + 2;
		while (line[i] == ' ')
			i++;
		total++;
		if (line[i] == '\'' || line[i] == '\"')
		{
			c = line[i];
			i++;
			while (line[i] && line[i] != c )
			{
				if (line[i] == '\\' && line[i + 1])
					i = i + 2;
				i++;
			}
			i++;
		}
		else
			while (line[i] != ' ' && line[i] != '\''  && line[i] != '\"' && line[i])
				i++;
	}
	return (total);
}

int		malloc_size(char *str)
{
	int i;
	char c;

	i = 0;
	c = str[i];
	while (str[i])
	{
		if (str[i] == '\\')
			i = i + 2;
		if (c == '\'' || c == '\"')
		{
			if (str[++i] == c)
				return (i + 2);
		}
		else if (str[i] == ' ')
		{
				i++;
				return (i + 1);
		}
		else
			i++;
	}
	return (i + 1);
}

char	*build_arg(char *str, int *j)
{
	int i;
	char *tmp;
	char c;

	i = 0;
	tmp = (char *)malloc(sizeof(char *) * malloc_size(str));
	c = str[i];
	while (str[i])
	{
		while (str[i] == '\\' || str[i - 1] == '\\')
		{
			tmp[i] = str[i];
			i++;
		}
		if (c == '\'' || c == '\"')
		{
			if (c == str[i] && i != 0)
			{
				tmp[i] = str[i];
				i++;
				if (str[i] == ' ')
					tmp[i++] = ' ';
				break;
			}
			else
				tmp[i] = str[i];
		}
		else if (str[i] == ' ' || str[i] == '\'' || str[i] == '\"')
		{
			if ((str[i] == '\'' || str[i] == '\"') && str[i + 1] == ' ')
				tmp[i++] = ' ';
			break;
		}
		else
			tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	*j = i + *j;
	return (tmp);
}

char	**first_split(char *line)
{
	int i;
	int j;
	char **args;
	int total;

	i = 0;
	j = 0;
	total = total_argus(line);
	args = (char **)malloc(sizeof(char *) * total);
	args[total - 1] = NULL;
	while (i < total)
	{
		while (line[j] == ' ')
			j++;
		args[i] = build_arg(&line[j], &j);
		i++;
	}
	*(args + i) = NULL;
	while (i < total - 1)
	{
		printf(" full arg == %s\n", args[i]);
		i++;
	}
	return (args);
}
