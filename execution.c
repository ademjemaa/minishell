/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 21:20:12 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/18 00:31:34 by abarbour         ###   ########.fr       */
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

int    exec_pipe(t_cmd **tab, int *i, char **envp)
{
    int input_fd;
    int pip[2];
	int	old_pid;
	int	status;

    input_fd = 0;
    while (tab[*i] && tab[*i]->sep == 4)
    {
        pipe(pip);
		if (tab[*i]->red == 3)
        	exec_prog(input_fd, cr_files(tab[*i]), tab[*i], envp);
		else
        	exec_prog(input_fd, pip[1], tab[*i], envp);
        close(pip[1]);
        input_fd = pip[0];
        (*i)++;
    }
    pipe(pip);
	if (tab[*i]->red == 3)
       	old_pid = exec_prog(input_fd, cr_files(tab[*i]), tab[*i], envp);
	else
    	old_pid = exec_prog(input_fd, pip[1], tab[*i], envp);
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
			if (c != 3)
            	write(1,&c,1);
    }
}
