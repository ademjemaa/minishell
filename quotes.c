/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:05:56 by adjemaa           #+#    #+#             */
/*   Updated: 2021/02/22 13:35:54 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		fix_quotes(t_check *check, char *str)
{
	if (str[check->i] == '\'' && check->two == 0)
	{
		check->one = !(check->one);
		check->i++;
		return (0);
	}
	else if (str[check->i] == '\"' && check->one == 0)
	{
		check->two = !(check->two);
		check->i++;
		return (0);
	}
	return (1);
}

int		final_size(char *str, char *envp)
{
	int i;
	int total;
	int j;

	i = 0;
	j = -1;
	total = 1;
	while (str[i++] != '$')
		total++;
	while (envp != NULL && envp[++j])
		total++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' &&
				str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') ||
				str[i] == '_'))
			i++;
	else
		i++;
	while (str[i])
	{
		total++;
		i++;
	}
	return (total);
}

int		env_len(char *str)
{
	int i;

	i = 1;
	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' &&
			str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') ||
			str[i] == '_'))
		i++;
	return (i);
}

int		quote_status(t_check *c, char *str)
{
	if (str[0] == '\"' && str[1] != '\"' && !(c->one))
		c->two = !(c->two);
	else if (str[0] == '\'' && str[1] != '\'' && !(c->two))
		c->one = !(c->one);
	else if (str[0] == '\"' && str[1] == '\"' && !(c->one) &&
			!(c->env) && str[2] == ' ' && str[3] == ' ')
	{
		c->i = c->i + 2;
		return (0);
	}
	else if (str[0] == '\'' && str[1] == '\'' && !(c->two)
			&& str[2] == ' ' && str[3] == ' ')
	{
		c->i = c->i + 2;
		return (0);
	}
	return (1);
}

char	*exact_env(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * env_len(str));
	if (tmp == NULL)
		return (NULL);
	if (str[0] >= '0' && str[0] <= '9')
		tmp[i] = str[i];
	else
	{
		while (str[i] && env_chars(str[i], 1))
		{
			tmp[i] = str[i];
			i++;
		}
	}
	tmp[i] = 0;
	return (tmp);
}
