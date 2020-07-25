/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 00:26:53 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/26 00:20:16 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		dispatch_built_in(char *path, char **args, char **envp)
{
	if (!ft_strncmp(path, "echo", 5))
		return (ft_echo(path, args, envp));
	else if (!ft_strncmp(path, "cd", 3))
		exit(ft_cd(path, args, envp));
	else if (!ft_strncmp(path, "pwd", 4))
		return (ft_pwd(path, args, envp));
	else if (!ft_strncmp(path, "export", 7))
		return (ft_echo(path, args, envp));
	else if (!ft_strncmp(path, "unset", 6))
		return (ft_echo(path, args, envp));
	else if (!ft_strncmp(path, "env", 4))
		return (ft_env(path, args, envp));
	return (-1);
}

int		exec_built_in(int in, int out, t_cmd *cmd, char **envp)
{
	int pid;

	if ((pid = fork ()) == 0)
	{
		if (out == -1 || in == -1)
			exit(1);
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
		if (dispatch_built_in(cmd->path, cmd->args, envp) == -1)
			ft_putstr_error(strerror(errno));
		if (errno == 2)
			exit(127);
		if (errno == 13)
			exit(126);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
