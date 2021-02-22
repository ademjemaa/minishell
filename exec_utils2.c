/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 23:20:05 by abarbour          #+#    #+#             */
/*   Updated: 2021/02/05 12:48:40 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concat_sbs_args(t_cmd *cmd, char **new_args, int *i, int *j)
{
	new_args[*j] = NULL;
	while (cmd->args[*i] && cmd->args[*i][0] &&
		(cmd->args[*i][ft_strlen(cmd->args[*i]) - 1] != ' ' ||
		 cmd->args[*i][ft_strlen(cmd->args[*i]) - 2] == '\\'))
	{
		new_args[*j] = ft_strjoinfree(new_args[*j],
				proc_arg(cmd->args, *i), 0);
		(*i)++;
	}
	if (cmd->args[*i])
	{
		if (cmd->args[*i][0])
			cmd->args[*i][ft_strlen(cmd->args[*i]) - 1] = '\0';
		new_args[*j] = ft_strjoinfree(new_args[*j],
				proc_arg(cmd->args, *i), 0);
		(*i)++;
	}
	(*j)++;
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

int		is_env_built_in_cmd(t_cmd **tab, int i)
{
	if (tab[i]->path && tab[i]->sep != 4 &&
		(!ft_strncmp(tab[i]->path, "cd", 3)
		|| !ft_strncmp(tab[i]->path, "export", 7)
		|| !ft_strncmp(tab[i]->path, "exit", 5)
		|| !ft_strncmp(tab[i]->path, "unset", 6)
		|| !ft_strncmp(tab[i]->path, "echo", 5)))
		return (1);
	return (0);
}

void	dup_and_close(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
}
