/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:59:38 by abarbour          #+#    #+#             */
/*   Updated: 2021/02/05 13:10:56 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		narg_len_dq(char *arg)
{
	int		i;
	int		j;

	if (arg[0] != '"')
		return (0);
	i = 1;
	j = ft_strlen(arg) - 2;
	while (arg[i])
	{
		if (arg[i] == '\\' && (arg[i + 1] == '\\' || arg[i + 1] == '$'))
		{
			j--;
			i++;
		}
		i++;
	}
	if (arg[i - 1] != '"')
		return (0);
	return (j);
}

int		narg_len_nq(char *arg)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(arg);
	while (arg[i])
	{
		if (arg[i] == '\\')
		{
			j--;
			i++;
		}
		i++;
	}
	return (j);
}

int		narg_len_sq(char *arg)
{
	int		i;
	int		j;

	if (arg[0] != '\'')
		return (0);
	i = 1;
	j = ft_strlen(arg) - 2;
	while (arg[i])
		i++;
	if (arg[i - 1] != '\'')
		return (0);
	return (j);
}

int		nargs_count(char **args)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (args[i])
	{
		while (args[i] && (args[i][0] == '"' || args[i][0] == '\'')
			&& args[i][ft_strlen(args[i]) - 1] != ' ')
			i++;
		if (args[i] && args[i][0])
			j++;
		if (args[i])
			i++;
	}
	return (j);
}

void	rd_cr_files(t_cmd *c, int *in, int *out)
{
	int		i;

	i = -1;
	while (c->files[++i].file)
	{
		if (*in != 0)
			close(c->files[i].red == 1 ? *in : *out);
		if (c->files[i].red == 3 || c->files[i].red == 2)
			*out = open(c->files[i].file, O_CREAT | O_WRONLY | (c->files[i].red
			== 2 ? O_APPEND : O_TRUNC), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
			*in = open(c->files[i].file, O_RDONLY);
		if (*out == -1 || *in == -1)
		{
			ft_putstr_error(strerror(errno));
			break ;
		}
		if (c->files[i + 1].file && c->files[i + 1].red == 1 && *in != 0)
			close(*in);
		if (c->files[i + 1].file &&
			(c->files[i + 1].red == 2 || c->files[i].red == 2))
			close(*out);
	}
}
