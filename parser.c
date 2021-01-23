/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 15:52:17 by abarbour          #+#    #+#             */
/*   Updated: 2021/01/23 16:18:22 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		counter(char *line)
{
	int		total;
	t_check c;

	total = 1;
	init_struct(&c);
	while (line[c.i])
	{
		sep_quotes(&c, &line[c.i]);
		if (line[c.i] == ';' || line[c.i] == '|')
			total++;
		if (line[c.i] != 0)
			c.i++;
	}
	return (total);
}

char	*cmd_name(char *line)
{
	int		i;
	int		nb_c;
	char	*str;

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
	return (create_cmd_name(line, nb_c));
}

char	*path_parser(char *line, char **envp, t_cmd *tmp)
{
	char			*stri;
	struct stat		sb;
	int				i;

	tmp->built = 0;
	i = 0;
	tmp->prog = 0;
	stri = cmd_name(line);
	if (stri == NULL)
		return (NULL);
	while (stri[i] && stri[i] != '/')
		i++;
	if (stri[i] == '/')
	{
		tmp->prog = 1;
		if (stat(&stri[i], &sb) == 0)
			return (stri);
	}
	if (check_name(line, tmp))
		return (stri);
	free(stri);
	return (ret_handler(line, envp, &sb));
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

	total = counter(line);
	init_struct(&c);
	tab = (t_cmd**)malloc(sizeof(t_cmd**) * (total + 1));
	if (tab == NULL)
		return (NULL);
	while (line[c.i])
	{
		tab[c.j] = params(&line[c.i], envp);
		c.j++;
		sep_quotes(&c, line);
		if (line[c.i])
			c.i++;
	}
	tab[c.j] = NULL;
	return (tab);
}
