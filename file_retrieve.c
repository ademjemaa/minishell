/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_retrieve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 18:38:18 by adjemaa           #+#    #+#             */
/*   Updated: 2021/01/28 12:04:16 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_status(t_check *check, char *str, char **envp, char *new)
{
	int		t;
	int		b;
	char	*tmp;

	t = 0;
	b = 0;
	if (fix_quotes(check, str) && str[check->i] == '$' && check->one == 0)
	{
		tmp = exact_env(&str[check->i + 1]);
		while (envp[t] != NULL && ft_strncmp(envp[t], tmp,
					envp_len(envp[t], tmp)))
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
			break ;
		i++;
	}
	if (j > i)
		i = j;
	return (i);
}

int		env_tran_len(char *str, char **envp, int *i)
{
	int		c;
	int		j;
	int		t;
	char	*tmp;

	c = 0;
	j = 0;
	tmp = exact_env(&str[1]);
	t = 1;
	while (envp[c] != NULL && ft_strncmp(envp[c], tmp, envp_len(envp[c], tmp)))
		c++;
	while (str[t] && ((str[t] >= 'a' && str[t] <= 'z') || (str[t] >= 'A' &&
		str[t] <= 'Z') || (str[t] >= '0' && str[t] <= '9') || str[t] == '_'))
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
	int		total;
	t_check c;

	total = 1;
	init_struct(&c);
	while (str[c.i] && str[c.i] != ' ' && str[c.i] != '>' && str[c.i] != '<')
	{
		if (str[c.i] == '\\' && c.one == 0)
		{
			(c.i)++;
			total++;
		}
		if (str[c.i] == '\'' && !(c.two))
			c.one = !(c.one);
		else if (str[c.i] == '\"' && !(c.one))
			c.two = !(c.two);
		else if (str[c.i] == '$' && c.one == 0 && str[c.i - 1] != '\\')
			total = total + env_tran_len(&str[c.i], envp, &c.i);
		else
			total++;
		if (str[c.i] != 0)
			(c.i)++;
	}
	return (total);
}

char	*retrieve(char *str, char **envp)
{
	char	*tmp;
	t_check	c;

	init_struct(&c);
	tmp = malloc(sizeof(char *) * file_len(str, envp));
	if (tmp == NULL)
		return (NULL);
	tmp[file_len(str, envp)] = 0;
	while (str[c.i])
	{
		if (str[c.i] == '\\' && c.one == 0)
			copy_slash(tmp, str, &c);
		else if ((str[c.i] == '\'' && c.two == 0) ||
				(str[c.i] == '\"' && c.one == 0))
			change_status(&c, str, envp, tmp);
		else if (str[c.i] == '$' && c.one == 0)
			change_status(&c, str, envp, tmp);
		else
			tmp[c.j++] = str[c.i++];
	}
	tmp[c.j] = 0;
	return (tmp);
}
