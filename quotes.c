/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:05:56 by adjemaa           #+#    #+#             */
/*   Updated: 2020/06/04 19:06:25 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		final_size(char *str, char *envp)
{
	int i;
	int total;
	int j;

	i = -1;
	j = -1;
	total = 1;
	while (str[++i] != '$')
		total++;
	while (envp != NULL && envp[++j])
		total++;
	i++;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
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
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
		i++;
	return (i);
}

int		quote_status(t_check *c, char *str)
{

	if (str[0] == '\"' && str[1] != '\"' && !(c->one))
		c->two = !(c->two);
	else if (str[0] == '\'' && str[1] != '\'' && !(c->two))
		c->one = !(c->one);
	else if (str[0] == '\"' && str[1] == '\"' && !(c->one) && !(c->env))
	{
		c->i = c->i + 2;
		return (0);
	}
	else if (str[0] == '\'' && str[1] == '\'' && !(c->two))
	{
		c->i = c->i + 2;
		return (0);
	}
	return (1);
}

char	*exact_env(char *str)
{
	char *tmp;
	int i;

	i = 0;
	tmp = malloc(sizeof(char *) * env_len(str));
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
