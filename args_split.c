/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 18:01:22 by adjemaa           #+#    #+#             */
/*   Updated: 2020/08/01 17:53:14 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		total_argus(char *line)
{
	int i;
	int total;

	total = 1;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i])
			total++;
		if (line[i] == '>' || line[i] == '<')
			i = line_return(&line[i]) + i;
		if (line[i] == '\'' || line[i] == '\"')
			quotes_cal(line, &i);
		else
		{
			while (line[i] != ' ' && line[i] != '\'' && line[i] != '\"' &&
					line[i] && line[i] != '>' && line[i] != '<')
				if (line[i++] == '\\')
					i++;
		}
	}
	return (total);
}

int		malloc_size(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	while (str[i])
	{
		if (str[i] == '\\')
			i = i + 2;
		if (str[i] == '>' || str[i] == '<')
			return (line_return(&str[i]) + 1);
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
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * (malloc_size(str) + 2));
	if (str[0] == '>' || str[0] == '<')
		return (file_prot(str, tmp, j));
	while (str[i])
	{
		if (arg_handler(str, tmp, &i) == 1)
			break ;
		i++;
	}
	tmp[i] = 0;
	*j = i + *j;
	return (tmp);
}

char	**first_split(char *line)
{
	int		i;
	int		j;
	char	*str;
	char	**args;
	int		total;

	i = 0;
	j = 0;
	total = total_argus(line);
	args = (char **)malloc(sizeof(char *) * (total));
	args[total] = NULL;
	while (i < total - 1)
	{
		while (line[j] == ' ')
			j++;
		str = build_arg((line + j), &j);
		args[i] = str;
		i++;
	}
	args[i] = NULL;
	return (args);
}
