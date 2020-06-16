/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 21:20:12 by abarbour          #+#    #+#             */
/*   Updated: 2020/06/16 21:56:30 by abarbour         ###   ########.fr       */
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

void    exec_prog(int in, int out, t_cmd *cmd, char **envp)
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
        execve(cmd->path, cmd->args, envp);
    }
}

int    exec_pipe(t_cmd **tab, int *i, char **envp)
{
    int input_fd;
    int pip[2];

    input_fd = 0;
    while (tab[*i] && tab[*i]->sep == 4)
    {
        pipe(pip);
        exec_prog(input_fd, pip[1], tab[*i], envp);
        close(pip[1]);
        input_fd = pip[0];
        (*i)++;
    }
    pipe(pip);
    exec_prog(input_fd, pip[1], tab[*i], envp);
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
        if (!(tab[i]->path))//lehna lazem gestion d'erreur
            i++;
		proc_args(tab[i]);
        output = exec_pipe(tab, &i, envp);
        while (read(output,&c,1) > 0)
            write(1,&c,1);
    }
}
