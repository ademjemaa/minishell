/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 00:26:53 by abarbour          #+#    #+#             */
/*   Updated: 2021/02/05 13:18:38 by abarbour         ###   ########.fr       */
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

int		return_built_in(t_cmd *cmd, char ***envp, int oout, int p)
{
	if (!ft_strncmp(cmd->path, "echo", 5))
		return (btin_ret(ft_echo(cmd->args), oout, p));
	else if (!ft_strncmp(cmd->path, "cd", 3))
		return (btin_ret(ft_cd(cmd->args, envp), oout, p));
	else if (!ft_strncmp(cmd->path, "pwd", 4))
		return (btin_ret(ft_pwd(), oout, p));
	else if (!ft_strncmp(cmd->path, "export", 7))
		return (btin_ret(ft_export(cmd->args, envp, p), oout, p));
	else if (!ft_strncmp(cmd->path, "unset", 6))
		return (btin_ret(ft_unset(cmd->args, envp, p), oout, p));
	else if (!ft_strncmp(cmd->path, "env", 4))
		return (btin_ret(ft_env(*envp), oout, p));
	else if (!ft_strncmp(cmd->path, "exit", 5))
		return (btin_ret(ft_exit(cmd->args), oout, p));
	return (-1);
}

int		dispatch_built_in(t_cmd *cmd, char ***envp, int p)
{
	int		out;
	int		oout;

	out = 0;
	oout = 0;
	if (!p)
	{
		rd_cr_files(cmd, &oout, &out);
		if (oout == -1 || out == -1)
			return (-2);
		oout = dup(1);
		if (out)
		{
			dup2(out, 1);
			close(out);
		}
	}
	return (return_built_in(cmd, envp, oout, p));
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
