/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 18:01:22 by adjemaa           #+#    #+#             */
/*   Updated: 2021/01/28 12:04:06 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		total_argus(char *line)
{
	t_check c;

	init_struct(&c);
	while (line[c.i])
	{
		while (line[c.i] == ' ')
			c.i++;
		if (line[c.i])
			c.env++;
		if (line[c.i] == '>' || line[c.i] == '<' || c.j++ == 0)
			c.i = line_return(&line[c.i]) + c.i;
		if ((line[c.i] == '\'' || line[c.i] == '\"') && c.j)
			quotes_cal(line, &(c.i));
		else
		{
			while (line[c.i] != ' ' && line[c.i] != '\'' && line[c.i] != '\"' &&
					line[c.i] && line[c.i] != '>' && line[c.i] != '<')
				if (line[c.i++] == '\\')
					c.i++;
		}
	}
	return (c.env + 1);
}

int		malloc_size(char *str, int cur, char **args)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	while (str[i])
	{
		if (str[i] == '\\')
			i = i + 2;
		if (str[i] == '>' || str[i] == '<' || check_cmd(args, cur))
			return (line_return(&str[i]) + 1);
		if (c == '\'' || c == '\"')
		{
			if (str[++i] == c)
				return (i + 2);
		}
		else if (str[i] == ' ')
			return (i + 2);
		else
			i++;
	}
	return (i + 1);
}

char	*build_arg(char *str, int *j, int cur, char **args)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * (malloc_size(str, cur, args)));
	if (tmp == NULL)
		return (NULL);
	if (str[0] == '>' || str[0] == '<' || check_cmd(args, cur))
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
	if (args == NULL)
		return (NULL);
	while (i < total - 1)
	{
		while (line[j] == ' ')
			j++;
		str = build_arg((line + j), &j, i, args);
		args[i] = str;
		i++;
	}
	args[i] = NULL;
	return (args);
}
