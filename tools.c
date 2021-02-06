/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 18:00:48 by adjemaa           #+#    #+#             */
/*   Updated: 2021/01/30 16:13:24 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		size_counter(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (str[i])
	{
		quote_limits(str, &j, &i);
		if (((str[i] == '>' || str[i] == '<') && str[i + 1] == ' '))
			while (str[i + 1] == ' ')
				i++;
		else
			i++;
	}
	return (j + 1);
}

char	*rearrange(char *str)
{
	char	*tmp;
	t_check	c;

	init_struct(&c);
	tmp = malloc(sizeof(char) * size_counter(str));
	if (tmp == NULL)
		return (NULL);
	tmp[size_counter(str) - 1] = 0;
	while (c.i < size_counter(str))
	{
		copy_quotes(str, tmp, &c);
		c.i++;
		c.j++;
	}
	free(str);
	return (tmp);
}

char	*change_str(char *envp, char *str)
{
	t_check	c;
	char	*tmp;

	init_struct(&c);
	while (envp != NULL && envp[c.j] && envp[c.j] != '=')
		c.j++;
	c.j++;
	tmp = malloc(sizeof(char) * (final_size(str, envp)));
	envp_slash(str, tmp, &c, envp);
	while (str[c.i])
	{
		tmp[c.env] = str[c.i];
		c.env++;
		c.i++;
	}
	free(str);
	tmp[c.env] = 0;
	return (tmp);
}

void	find_env(char **args, char **envp)
{
	t_check c;

	init_struct(&c);
	if (args == NULL)
		return ;
	while (args[c.i] != NULL)
	{
		c.j = -1;
		if (args[c.i][0] != '\'')
		{
			while (args[c.i][++c.j])
			{
				single_q_status(args[c.i], &c);
				if (args[c.i][c.j] == '\\')
					c.j = c.j + 1;
				else if (args[c.i][c.j] == '$' && args[c.i][c.j + 1]
					&& args[c.i][c.j + 1] != '\"' && c.one == 0)
				{
					args[c.i] = swap_case(args[c.i], envp, c.j + 1);
					c.j = -1;
				}
			}
		}
		c.i++;
	}
}

int		red_type(char *str)
{
	int i;
	int one;
	int two;
	int ret;

	i = -1;
	one = 0;
	two = 0;
	ret = 0;
	while (str[++i])
	{
		while (str[i] == '\\' && one == 0)
			i = i + 2;
		if (str[i] == '\'' && !two)
			one = !one;
		if (str[i] == '\"' && !one)
			two = !two;
		if ((str[i] == '>' || str[i] == '<') && one == 0 && two == 0)
			ret = find_filered(&str[i]);
	}
	if (one || two)
		ret = -1;
	return (ret);
}
