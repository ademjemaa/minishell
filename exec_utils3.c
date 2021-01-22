/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 20:41:45 by abarbour          #+#    #+#             */
/*   Updated: 2020/08/08 20:46:39 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	begin_pipe(t_cmd **tab, char ***envp, int *i)
{
	int		old_pid;
	int		status;

	g_childs = 1;
	old_pid = exec_pipe(tab, i, envp);
	waitpid(old_pid, &status, 0);
	g_exit_code = WIFSIGNALED(status) ? 128 + WTERMSIG(status)
		: WEXITSTATUS(status);
	g_childs = 0;
}
