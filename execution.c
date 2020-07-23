/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 21:20:12 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/24 00:09:40 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_pipes(t_cmd **tab)
{
    int i;

    i = 0;
    while (tab[i] && tab[i]->sep == 3)
        i++;
    return (i);
}

int    exec_prog(int in, int out, t_cmd *cmd, char **envp)
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
		if (execve(cmd->path, cmd->args, envp) == -1)
			ft_putstr_error(strerror(errno));
		if (errno == 2)
			exit(127);
		if (errno == 13)
			exit(126);
		exit(EXIT_FAILURE);
    }
	return (pid);
}

int		perform_redirects(t_cmd *tab, int input_fd, int *pip, char **envp)
{
	int		old_pid;
	int		in;
	int		out;

	in = input_fd;
	out = pip[1];
	if (tab->red == 3 || tab->red == 2 || tab->red == 1)
	{
		rd_cr_files(tab, &in, &out);
       	old_pid = exec_prog(in, out, tab, envp);
	}
	else
       	old_pid = exec_prog(input_fd, pip[1], tab, envp);
	return (old_pid);
}

int		exec_pipe(t_cmd **tab, int *i, char **envp)
{
    int input_fd;
    int pip[2];
	int	old_pid;
	int	status;

    input_fd = 0;
    while (tab[*i] && tab[*i]->sep == 4)
    {
        pipe(pip);
		perform_redirects(tab[*i], input_fd, pip, envp);
        close(pip[1]);
        input_fd = pip[0];
        (*i)++;
    }
    pipe(pip);
	old_pid = perform_redirects(tab[*i], input_fd, pip, envp);
	waitpid(old_pid, &status, 0);
	if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else
		exit_code = WEXITSTATUS(status);
    close(pip[1]);
    (*i)++;
    return (pip[0]);
}

void    exec(t_cmd **tab, char **envp)
{
    int     i;
    char    c;
    int     pip[2];
    int     output;

    i = 0;
    while (tab[i])
    {
		concat_args(tab[i]);
        output = exec_pipe(tab, &i, envp);
        while (read(output,&c,1) > 0)
            	write(1,&c,1);
    }
}
