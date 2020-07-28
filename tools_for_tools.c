/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:20:26 by adjemaa           #+#    #+#             */
/*   Updated: 2020/07/28 09:50:06 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	copy_quotes(char *str, char *tmp, t_check *c)
{
	while (str[c->j] == '\\' && str[c->j + 1])
	{
		tmp[(c->i)++] = str[(c->j)++];
		tmp[(c->i)++] = str[(c->j)++];
	}
	if (str[c->j] == '\'' && c->two == 0)
		c->one = !c->one;
	if (str[c->j] == '\"' && c->one == 0)
		c->two = !c->two;
	if (((str[c->j + 1] == '>' && str[c->j] != '>') || (str[c->j + 1] ==
		'<')) && str[c->j] != ' ' && c->one == 0 && c->two == 0)
	{
		tmp[c->i] = str[c->j];
		c->i++;
		tmp[c->i] = ' ';
	}
	else if ((str[c->j] == ' ') && (str[c->j - 1] == '>' || str[c->j - 1] ==
			'<') && c->one == 0 && c->two == 0)
	{
		while (str[c->j] == ' ')
			c->j++;
		tmp[c->i] = str[c->j];
	}
	else
		tmp[c->i] = str[c->j];
}

void	envp_slash(char *str, char *tmp, t_check *c, char *envp)
{
	while (str[c->i++] && str[c->i] != '$')
	{
		if (str[c->i] == '\\')
		{
			tmp[c->env] = str[c->i];
			c->env++;
			c->i++;
		}
		tmp[c->env] = str[c->i];
		c->env++;
	}
	while (envp != NULL && envp[c->j])
		tmp[c->env++] = envp[c->j++];
	while (str[c->i] && ((str[c->i] >= 'a' && str[c->i] <= 'z') || (str[c->i]
			>= 'A' && str[c->i] <= 'Z') || (str[c->i] >= '0' &&
			str[c->i] <= '9') || str[c->i] == '_'))
		c->i++;
}
