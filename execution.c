#include "minishell.h"

void exec(t_cmd ** tab, char **envp)
{
    int     i;
    int     id;
    char    c;
    int     pip[2];

    i = 0;
    while (tab[i])
    {
        pipe(pip);
        id = fork();
        if (id == 0)
        {
            close(pip[0]);
            dup2(pip[1], 1);
            execve(tab[i]->path, tab[i]->args, envp);
            close(pip[1]);
            exit(0);
        }
        else
        {
            close(pip[1]);
            while (read(pip[0],&c,1) > 0)
            {
                write(1,&c,1);
            }
        }
        i++;
    }
}