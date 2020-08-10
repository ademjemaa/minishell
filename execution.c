/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 21:20:12 by abarbour          #+#    #+#             */
/*   Updated: 2020/08/10 23:03:24 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_pipes(t_cmd **tab)
{
	int i;

	i = 0;
	while (tab[i] && tab[i]->sep == 3)
		i++;
	return (i);
}

int		exec_prog(int in, int out, t_cmd *cmd, char ***envp)
{
	int pid;

	if ((pid = fork()) == 0)
	{
		if (out == -1 || in == -1)
			exit(1);
		dup_and_close(in, out);
		if (!(cmd->path))
		{
			ft_putstr_error(strerror(2));
			exit(127);
		}
		if (cmd->path && execve(cmd->path, cmd->args, *envp) == -1)
			ft_putstr_error(strerror(errno));
		if (errno == 2)
			exit(127);
		if (errno == 13)
			exit(126);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int		perform_redirects(t_cmd *tab, int input_fd, int *pip, char ***envp)
{
	int		old_pid;
	int		in;
	int		out;

	in = input_fd;
	out = pip[1];
	if (tab->red == 3 || tab->red == 2 || tab->red == 1)
	{
		rd_cr_files(tab, &in, &out);
		if (tab->built)
			old_pid = exec_built_in(in, out, tab, envp);
		else
			old_pid = exec_prog(in, out, tab, envp);
	}
	else
	{
		if (tab->built)
			old_pid = exec_built_in(in, out, tab, envp);
		else
			old_pid = exec_prog(input_fd, pip[1], tab, envp);
	}
	return (old_pid);
}

int		exec_pipe(t_cmd **tab, int *i, char ***envp)
{
	int		input_fd;
	int		pip[2];
	int		old_pid;
	char	c;

	input_fd = 0;
	concat_args(tab[*i]);
	while (tab[*i] && tab[*i]->sep == 4)
	{
		pipe(pip);
		perform_redirects(tab[*i], input_fd, pip, envp);
		close(pip[1]);
		input_fd = pip[0];
		(*i)++;
		concat_args(tab[*i]);
	}
	pipe(pip);
	old_pid = perform_redirects(tab[*i], input_fd, pip, envp);
	close(pip[1]);
	while (read(pip[0], &c, 1) > 0)
		write(1, &c, 1);
	(*i)++;
	return (old_pid);
}

void	exec(t_cmd ***tab, char ***envp, char *line)
{
	int		i;
	int		old_pid;
	int		status;

	i = 0;
	while ((*tab)[i])
	{
		if (is_env_built_in_cmd(*tab, i))
		{
			if (((*tab)[i])->red != -1)
				concat_args((*tab)[i]);
			if (dispatch_built_in(((*tab)[i])->path,
				((*tab)[i])->args, envp, 0) == -1)
			{
				g_exit_code = 1;
				if (errno)
					ft_putstr_error(strerror(errno));
			}
			i++;
		}
		else
			begin_pipe(*tab, envp, &i);
		free_cmds(*tab);
		*tab = parser(line, *envp);
	}
}
