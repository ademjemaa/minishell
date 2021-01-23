/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 00:26:53 by abarbour          #+#    #+#             */
/*   Updated: 2021/01/23 17:21:42 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		btin_ret(int ret, int old_out, int p)
{
	if (!p)
	{
		dup2(old_out, 1);
		close(old_out);
	}
	return (ret);
}

int		dispatch_built_in(t_cmd *cmd, char ***envp, int p)
{
	int		out;
	int		oout;

	out = 0;
	if (!p)
	{
		rd_cr_files(cmd, &out, &out);
		oout = dup(1);
		dup2(out, 1);
	}
	if (!ft_strncmp(cmd->path, "echo", 5))
		return (ft_echo(cmd->path, cmd->args, *envp));
	else if (!ft_strncmp(cmd->path, "cd", 3))
		return (btin_ret(ft_cd(cmd->path, cmd->args, envp), oout, p));
	else if (!ft_strncmp(cmd->path, "pwd", 4))
		return (ft_pwd(cmd->path, cmd->args, *envp));
	else if (!ft_strncmp(cmd->path, "export", 7))
		return (btin_ret(ft_export(cmd->path, cmd->args, envp, p), oout, p));
	else if (!ft_strncmp(cmd->path, "unset", 6))
		return (btin_ret(ft_unset(cmd->path, cmd->args, envp, p), oout, p));
	else if (!ft_strncmp(cmd->path, "env", 4))
		return (ft_env(cmd->path, cmd->args, *envp));
	else if (!ft_strncmp(cmd->path, "exit", 5))
		return (ft_exit(cmd->path, cmd->args, envp));
	return (-1);
}

int		exec_built_in(int in, int out, t_cmd *cmd, char ***envp)
{
	int pid;

	if ((pid = fork()) == 0)
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
		if ((out = dispatch_built_in(cmd, envp, 1)) == -1)
			ft_putstr_error(strerror(errno));
		if (errno == 2)
			exit(127);
		if (errno == 13)
			exit(126);
		exit(out == 0 ? 0 : EXIT_FAILURE);
	}
	return (pid);
}
