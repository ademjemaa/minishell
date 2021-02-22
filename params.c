/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 23:14:11 by adjemaa           #+#    #+#             */
/*   Updated: 2021/02/22 13:27:56 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_find(char *line, t_cmd *stru)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	i = cmd_length(line);
	if (line[i] == ';')
		stru->sep = 5;
	else if (line[i] == '|')
		stru->sep = 4;
	else if (line[i] == 0)
		stru->sep = 0;
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i] = 0;
	j = -1;
	while (++j < i)
		str[j] = line[j];
	return (str);
}

char	*args_parser(char *str, char **envp, t_cmd *stru)
{
	char	**args;
	char	*tmp;

	tmp = str_find(str, stru);
	tmp = cleaned(tmp);
	args = first_split(tmp);
	stru->files = NULL;
	stru->file = NULL;
	stru->files = find_filelst(args, envp);
	find_env(args, envp);
	stru->args = find_path(args, stru, envp);
	find_spaces(stru);
	return (tmp);
}

int		sep_parser(char *str, t_cmd *tmp)
{
	int i;

	i = 0;
	tmp->red = -1;
	while (str[i] != 0 && str[i] != '|' && str[i] != ';')
		i++;
	while (str[i] != 0 && str[i] != '|' && str[i] != ';')
		i++;
	if (str[i] == ';')
		return (5);
	else if (str[i] == '|')
		return (4);
	else if (str[i] == 0)
		return (0);
	else
		return (-1);
}

int		check_name(char *str, t_cmd *tmp)
{
	int		ret;

	ret = 0;
	tmp->built = 0;
	if (str != NULL)
	{
		if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd") ||
			!ft_strcmp(str, "export") || !ft_strcmp(str, "unset") ||
			!ft_strcmp(str, "env") || !ft_strcmp(str, "exit"))
		{
			ret = 1;
			tmp->built = 1;
		}
	}
	else
		tmp->built = 0;
	return (ret);
}
