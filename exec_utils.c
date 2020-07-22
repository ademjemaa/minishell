/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:59:38 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/23 00:15:04 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		narg_len_dq(char *arg)
{
	int		i;
	int		j;

	if (arg[0] != '"')
		return (0);//lazem gestion d'erreur
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
		return (0);//lazem gestion d'erreur
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
		return (0);//lazem gestion d'erreur
	i = 1;
	j = ft_strlen(arg) - 2;
	while (arg[i])
		i++;
	if (arg[i - 1] != '\'')
		return (0);//lazem gestion d'erreur
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
		j++;
		if (args[i])
			i++;
	}
	return (j);
}

int		cr_files(t_cmd *cmd, int out)
{
	int		i;
	int		fd;

	i = -1;
	fd = -2;
	while (cmd->files[++i].file)
	{
		printf("!!!!!!%d\n", cmd->files[i].red);
		if (cmd->files[i].red == 3 || cmd->files[i].red == 2)
			fd = open(cmd->files[i].file, (cmd->files[i].red == 2 ? 513 : 1537),
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
		{
			while (cmd->files[i].file && cmd->files[i].red == 1)
				i++;
			i--;
		}
		if (fd == -1)
		{
			ft_putstr_error(strerror(errno));
			return (-1);
		}
		if (cmd->files[i + 1].file)
			close(fd);
	}
	return (fd == -2 ? out : fd);
}

void	ft_putstr_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, str + i, 1);
		i++;
	}
	write(2, "\n", 1);
}
