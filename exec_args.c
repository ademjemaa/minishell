/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 21:20:08 by abarbour          #+#    #+#             */
/*   Updated: 2020/06/21 23:46:06 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_dq(char	*arg)
{
	char	*str;
	int		j;
	int		i;

	if (!(str = malloc(narg_len_dq(arg))))
		return (NULL);
	j = 0;
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '\\' && (arg[i + 1] == '\\' || arg[i + 1] == '$'))
			i++;
		if (arg[i + 1])
			str[j++] = arg[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*remove_sq(char	*arg)
{
	char	*str;
	int		j;
	int		i;

	if (!(str = malloc(narg_len_sq(arg))))
		return (NULL);
	j = 0;
	i = 1;
	while (arg[i])
	{
		if (arg[i + 1])
			str[j++] = arg[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*proc_arg(char **args, int i)
{
	char	*tmp;

	if (args[i] && ((args[i][0] == '"') || (args[i][0] == '\'')))
	{
		tmp = args[i];
		if (args[i][0] == '"')
			args[i] = remove_dq(args[i]);
		else if (args[i][0] == '\'')
			args[i] = remove_sq(args[i]);
		free(tmp);
	}
	return (args[i]);
}

void	concat_args(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**new_args;

	i = 1;
	j = 1;
	if (!(new_args = (char **)malloc(sizeof(char*) * (nargs_count(cmd->args) + 2))))
		return;
	while (cmd->args[i])
	{
		new_args[j] = NULL;
		while (cmd->args[i] && (cmd->args[i][ft_strlen(cmd->args[i]) - 1] != ' '
			|| cmd->args[i][ft_strlen(cmd->args[i]) - 2] == '\\'))
		{
			new_args[j] = ft_strjoinfree(new_args[j], proc_arg(cmd->args, i), 0);
			i++;
		}
		if (cmd->args[i])
			cmd->args[i][ft_strlen(cmd->args[i]) - 1] = '\0';
		new_args[j] = ft_strjoinfree(new_args[j], proc_arg(cmd->args, i), 0);
		j++;
		if (cmd->args[i])
			i++;
	}
	new_args[0] = cmd->args[0];
	new_args[j] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

