/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 15:52:17 by abarbour          #+#    #+#             */
/*   Updated: 2020/08/08 20:05:07 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		counter(char *line)
{
	int total;
	int i;

	total = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|' || line[i] == ';')
			total++;
		i++;
	}
	return (total);
}

char	*cmd_name(char *line)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	if (line == NULL)
		return (NULL);
	while (line[j] == ' ' && line[j])
		j++;
	i = j;
	while (line[i] && line[i] != ' ')
		i++;
	str = malloc(sizeof(char) * (i - j + 1));
	if (str == NULL)
		return (NULL);
	str[i - j] = '\0';
	i = 0;
	while (line[j] != ' ' && line[j])
		str[i++] = line[j++];
	str[i] = 0;
	return (str);
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
		if (stat(&stri[i + 1], &sb) == 0)
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
	tmp->sep = sep_parser(line, tmp);
	tmp->red = red_type(str);
	free(str);
	return (tmp);
}

t_cmd	**parser(char *line, char **envp)
{
	int		total;
	t_cmd	**tab;
	int		i;
	int		j;

	i = 0;
	total = counter(line);
	j = 0;
	tab = (t_cmd**)malloc(sizeof(t_cmd**) * (total + 1));
	if (tab == NULL)
		return (NULL);
	while (line[j])
	{
		tab[i] = params(&line[j], envp);
		i++;
		while (line[j] && line[j] != '|' && line[j] != ';')
			j++;
		if (line[j])
			j++;
	}
	tab[i] = NULL;
	return (tab);
}
