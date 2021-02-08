/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_changer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 01:48:21 by adjemaa           #+#    #+#             */
/*   Updated: 2021/02/02 15:51:00 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_q_status(char *str, t_check *c)
{
	if (str[c->j] == '\'' && c->two == 0)
		c->one = !(c->one);
	if (str[c->j] == '\"' && c->one == 0)
		c->two = !(c->two);
}

char	*find_env_cmd(char *str, char **envp, char *stri)
{
	t_check	c;

	init_struct(&c);
	stri = ft_strdup(str);
	while (stri[c.i])
	{
		while (stri[c.i] == '\\')
			c.i = c.i + 2;
		if (stri[c.i] == '$' && c.one == 0 && stri[c.i + 1])
			stri = swap_case(stri, envp, c.i + 1);
		if (stri[c.i] == '\'' && c.two == 0)
			c.one = !(c.one);
		else if (stri[c.i] == '\"' && c.one == 0)
			(c.two) = !(c.two);
		c.i++;
	}
	return (stri);
}

char	*change_code(char *tmp, char *args, int j)
{
	int		i;
	char	*str;

	str = malloc(sizeof(char) * j + ft_strlen(tmp) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < j - 1)
	{
		str[i] = args[i];
		i++;
	}
	j = 0;
	while (tmp[j])
	{
		str[i] = tmp[j];
		i++;
		j++;
	}
	str[i] = 0;
	free(tmp);
	free(args);
	return (str);
}

char	*swap_case(char *args, char **envp, int j)
{
	char	*tmp;
	int		c;

	c = 0;
	if (args[j] == '?' && args[j] && args[j] != ' ')
	{
		tmp = ft_itoa(g_exit_code);
		tmp = ft_strjoinfree(tmp, &args[j + 1], 1);
		args = change_code(tmp, args, j);
	}
	else
	{
		tmp = exact_env(&args[j]);
		while (envp[c] != NULL && ft_strncmp(envp[c],
				tmp, envp_len(envp[c], tmp)))
			c++;
		if (((int)ft_strlen(tmp)) != 0)
			args = change_str(envp[c], args);
		free(tmp);
	}
	return (args);
}
