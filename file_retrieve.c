/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_retrieve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 18:38:18 by adjemaa           #+#    #+#             */
/*   Updated: 2020/06/22 01:51:14 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_status(t_check *check, char *str, char **envp, char *new)
{
	int t;
	int b;
	char *tmp;

	t = 0;
	b = 0;
	if (str[check->i] == '\'' && check->two == 0)
	{
		check->one = !(check->one);
		check->i++;
	}
	else if (str[check->i] == '\"' && check->one == 0)
	{
		check->two = !(check->two);
		check->i++;
	}
	else if (str[check->i] == '$' && check->one == 0)
	{
		tmp = exact_env(&str[check->i + 1]);
		while (envp[t] != NULL && ft_strncmp(envp[t], tmp, envp_len(envp[t], tmp)))
			t++;
		if (envp[t] != NULL)
		{
			while (envp[t][b] != '=')
				b++;
			while (envp[t][++b] != 0)
				new[check->j++] = envp[t][b];
			check->i = check->i + env_len(&str[check->i + 1]);
		}
		free(tmp);
		check->i++;
	}
}

int		envp_len(char *str, char *tmp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tmp[j])
		j++;
	while (str[i])
	{
		if (str[i] == '=')
			break;
		i++;
	}
	if (j > i)
		i = j;
	return (i);
}

int		env_tran_len(char *str, char **envp, int *i)
{
	int c;
	int j;
	int t;
	char *tmp;

	c = 0;
	j = 0;
	tmp = exact_env(&str[1]);
	t = 1;
	while (envp[c] != NULL  && ft_strncmp(envp[c], tmp, envp_len(envp[c], tmp)))
		c++;
	while (str[t] && ((str[t] >= 'a' && str[t] <= 'z') || (str[t] >= 'A' && str[t] <= 'Z') || (str[t] >= '0' && str[t] <= '9') || str[t] == '_'))
		t++;
	*i = t + *i;
	free(tmp);
	if (envp[c] != NULL)
	{
		while (envp[c][j] != '=')
			j++;
		return (ft_strlen(&envp[c][j + 1]));
	}
	return (0);
}

int		file_len(char *str, char **envp)
{
	int i;
	int total;
	int one;
	int two;

	total = 1;
	i = 0;
	one = 0;
	two = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\\' && one == 0)
		{
			i++;
			total++;
		}
		if (str[i] == '\'' && !two)
			one = !one;
		else if (str[i] == '\"' && !one)
			two = !two;
		else if (str[i] == '$' && one == 0 && str[i - 1] != '\\')
			total = total + env_tran_len(&str[i], envp, &i);
		else
			total++;
		if (str[i] != 0)
			i++;
	}
	return (total);
}

char	*retrieve(char *str, char **envp)
{
	char *tmp;
	t_check c;

	c.i = 0;
	c.j = 0;
	c.one = 0;
	c.two = 0;
	tmp = malloc(sizeof(char *) * file_len(str, envp));
	tmp[file_len(str, envp)] = 0;
	while (str[c.i])
	{
		if (str[c.i] == '\\' && c.one == 0)
		{
			tmp[c.j] = str[c.i];
			c.j++;
			c.i++;
			tmp[c.j] = str[c.i];
			c.j++;
			c.i++;
		}
		else if (str[c.i] == '\'' || str[c.i] == '\"')
			change_status(&c, str, envp, tmp);
		else if (str[c.i] == '$' && c.one == 0)
			change_status(&c, str, envp, tmp);
		else
		{
			tmp[c.j] = str[c.i];
			c.j++;
			c.i++;	
		}
	}
	tmp[c.j] = 0;
	return (tmp);
}
