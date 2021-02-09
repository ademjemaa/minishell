/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 20:41:45 by abarbour          #+#    #+#             */
/*   Updated: 2021/02/02 16:30:35 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*no_path(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}

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

void	reparse(t_cmd ***tab, char ***envp, char *line)
{
	free_cmds(*tab);
	*tab = NULL;
	*tab = parser(line, *envp);
}
