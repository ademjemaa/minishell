/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:20:26 by adjemaa           #+#    #+#             */
/*   Updated: 2021/01/28 15:05:33 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_cmd(char **args, int j)
{
	int i;

	i = 0;
	while (i < j)
	{
		if (args[i][0] == '>' || args[i][0] == '<')
			i++;
		else
			return (0);
	}
	return (1);
}

void	init_tmp(t_cmd *tmp)
{
	tmp->sep = 0;
	tmp->path = NULL;
	tmp->file = NULL;
	tmp->args = NULL;
	tmp->red = 0;
	tmp->prog = 0;
	tmp->built = 0;
}

void	quote_limits(char *str, int *j, int *i)
{
	char	c;

	while (str[*i] == '\\' && str[*i + 1])
	{
		*i = *i + 2;
		*j = *j + 2;
	}
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		c = str[*i];
		*i = *i + 1;
		*j = *j + 1;
		while (str[*i] && str[*i] != c)
		{
			*i = *i + 1;
			*j = *j + 1;
		}
	}
	if (((str[*i + 1] == '>' && str[*i] != '>') ||
		(str[*i + 1] == '<')) && str[*i] != ' ')
		*j = *j + 1;
	if (!((str[*i] == '>' || str[*i] == '<') && str[*i + 1] == ' '))
		*j = *j + 1;
}

void	copy_quotes(char *s, char *tmp, t_check *c)
{
	while (s[c->j] == '\\' && s[c->j + 1])
	{
		tmp[(c->i)++] = s[(c->j)++];
		tmp[(c->i)++] = s[(c->j)++];
	}
	if (s[c->j] == '\'' && c->two == 0)
		c->one = !c->one;
	if (s[c->j] == '\"' && c->one == 0)
		c->two = !c->two;
	if ((s[c->j] == ' ') && c->j != 0 && (s[c->j - 1] == '>' ||
			s[c->j - 1] == '<') && c->one == 0 && c->two == 0)
	{
		while (s[c->j] == ' ')
			c->j++;
		tmp[c->i] = s[c->j];
	}
	if ((s[c->j]) && (((s[c->j + 1] == '>' && s[c->j] != '>') ||
		(s[c->j + 1] == '<')) && s[c->j] != ' ' && c->one == 0 && c->two == 0))
	{
		tmp[c->i] = s[c->j];
		c->i++;
		tmp[c->i] = ' ';
	}
	else
		tmp[c->i] = s[c->j];
}

void	envp_slash(char *str, char *tmp, t_check *c, char *envp)
{
	while (str[c->i] && str[c->i] != '$')
	{
		if (str[c->i] == '\\')
		{
			tmp[c->env] = str[c->i];
			c->env++;
			c->i++;
		}
		tmp[c->env] = str[c->i];
		c->env++;
		c->i++;
	}
	c->i++;
	while (envp != NULL && envp[c->j])
		tmp[c->env++] = envp[c->j++];
	if (!(str[c->i] >= '0' && str[c->i] <= '9'))
		while (str[c->i] && ((str[c->i] >= 'a' && str[c->i] <= 'z') ||
		(str[c->i] >= 'A' && str[c->i] <= 'Z') || (str[c->i] >= '0' &&
		str[c->i] <= '9') || str[c->i] == '_'))
			c->i++;
	else
		c->i++;
}
