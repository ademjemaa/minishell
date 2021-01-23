/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 23:14:11 by adjemaa           #+#    #+#             */
/*   Updated: 2021/01/23 16:19:06 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sep_quotes(t_check *c, char *line)
{
	while (!(((line[c->i] == '|' || line[c->i] == ';') && c->env == 0) ||
		line[c->i] == '\0'))
	{
		if (line[c->i] == '\'' && c->two == 0)
		{
			c->one = !(c->one);
			c->env = !(c->env);
		}
		else if (line[c->i] == '\"' && c->one == 0)
		{
			c->two = !(c->two);
			c->env = !(c->env);
		}
		if (line[c->i] == '\\')
			c->i++;
		c->i++;
	}
}

char	*str_find(char *line, t_cmd *stru)
{
	t_check	c;
	char	*str;

	init_struct(&c);
	sep_quotes(&c, line);
	if (line[c.i] == ';')
		stru->sep = 5;
	else if (line[c.i] == '|')
		stru->sep = 4;
	else if (line[c.i] == 0)
		stru->sep = 0;
	str = malloc(sizeof(char) * (c.i + 1));
	if (str == NULL)
		return (NULL);
	str[c.i] = 0;
	while (c.j < c.i)
	{
		str[c.j] = line[c.j];
		c.j++;
	}
	return (str);
}

char	*args_parser(char *str, char **envp, t_cmd *stru)
{
	char	**args;
	char	*tmp;

	tmp = str_find(str, stru);
	tmp = cleaned(tmp);
	args = first_split(tmp);
	stru->files = NULL;
	stru->file = NULL;
	stru->files = find_filelst(args, envp);
	find_env(args, envp);
	stru->args = find_path(args, stru, envp);
	return (tmp);
}

int		check_name(char *line, t_cmd *tmp)
{
	int		ret;
	char	*str;

	ret = 0;
	tmp->built = 0;
	str = cmd_name(line);
	if (str != NULL)
	{
		if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd") ||
			!ft_strcmp(str, "export") || !ft_strcmp(str, "unset") ||
			!ft_strcmp(str, "env") || !ft_strcmp(str, "exit"))
		{
			ret = 1;
			tmp->built = 1;
		}
	}
	else
		tmp->built = 0;
	free(str);
	return (ret);
}
