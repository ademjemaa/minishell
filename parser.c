/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 15:52:17 by abarbour          #+#    #+#             */
/*   Updated: 2021/02/06 16:57:33 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		counter(char *line)
{
	t_check c;

	init_struct(&c);
	while (line[c.i])
	{
		while (line[c.i] == '\\' && c.one == 0)
			c.i = c.i + 2;
		if (line[c.i] == '\'' && c.two == 0)
			c.one = !c.one;
		if (line[c.i] == '\"' && c.one == 0)
			c.two = !c.two;
		if ((line[c.i] == '|' || line[c.i] == ';') &&
			line[c.i + 1] != '\0' && c.one == 0 && c.two == 0)
		{
			while (line[c.i + 1] == ' ')
				c.i++;
			if (line[c.i + 1])
				c.env++;
		}
		c.i++;
	}
	return (++c.env);
}

char	*cmd_name(char *line)
{
	int		i;
	int		nb_c;

	i = 0;
	nb_c = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			nb_c += nb_remove_sq(line, &i);
		if (line[i] == '\"')
			nb_c += nb_remove_dq(line, &i);
		else if (line[i])
		{
			nb_c++;
			i++;
		}
	}
	line = create_cmd_name(line, nb_c);
	return (line);
}

char	*path_parser(char *line, char **envp, t_cmd *tmp)
{
	char			*stri;
	struct stat		sb;
	int				i;

	i = 0;
	stri = NULL;
	stri = find_env_cmd(line, envp, stri);
	stri = cmd_name(stri);
	if (stri == NULL)
		return (NULL);
	while (stri[i] && stri[i] != '/')
		i++;
	if (stri[i] == '/')
	{
		tmp->prog = 1;
		if (stat(stri, &sb) == 0)
			return (stri);
	}
	if (check_name(stri, tmp))
		return (stri);
	return (ret_handler(stri, envp, &sb));
}

t_cmd	*params(char *line, char **envp)
{
	t_cmd	*tmp;
	char	*str;

	tmp = (t_cmd*)malloc(sizeof(t_cmd));
	if (tmp == NULL)
		return (NULL);
	init_tmp(tmp);
	str = args_parser(line, envp, tmp);
	tmp->red = red_type(str);
	free(str);
	return (tmp);
}

t_cmd	**parser(char *line, char **envp)
{
	int		total;
	t_cmd	**tab;
	t_check c;

	init_struct(&c);
	total = counter(line);
	tab = (t_cmd**)malloc(sizeof(t_cmd**) * (total + 1));
	if (tab == NULL)
		return (NULL);
	while (line[c.j])
	{
		tab[c.i] = params(&line[c.j], envp);
		c.i++;
		c.j = c.j + cmd_length(&line[c.j]);
		if (line[c.j])
			c.j++;
		while (line[c.j] == ' ')
			c.j++;
	}
	tab[c.i] = NULL;
	return (tab);
}
