#include "minishell.h"

int     size_counter(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (((str[i + 1] == '>' && str[i] != '>') || (str[i + 1] == '<')) && str[i] != ' ')
            j++;
        if (!((str[i] == '>' || str[i] == '<') && str[i + 1] == ' '))
            j++;
        if (((str[i] == '>' || str[i] == '<') && str[i + 1] == ' '))
            while (str[i + 1] == ' ')
                i++;
        else       
            i++;
    }
    return (j + 1);
}

char    *rearrange(char *str)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    j = 0;
    tmp = malloc(sizeof(char) * size_counter(str));
    tmp[size_counter(str) - 1] = 0;
    while (i < size_counter(str))
    {
        if (((str[j + 1] == '>' && str[j] != '>') || (str[j + 1] == '<')) && str[j] != ' ')
        {
            tmp[i] = str[j];
            i++;
            tmp[i] = ' ';
        }
        else if ((str[j] == ' ') && (str[j - 1] == '>' || str[j - 1] == '<'))
        {
            while (str[j] == ' ')
                j++;
            tmp[i] = str[j];
        }
        else
            tmp[i] = str[j];
        i++;
        j++;
    }
    free(str);
    return tmp;
}

char    *change_str(char *envp, char *str)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    j = 0;
    while (str[i] != '$' && str[i])
        i++;
    while (envp[j] && envp[j] != '=')
        j++;
    j++;
    tmp = malloc(sizeof(char) * (i + ft_strlen(&envp[j]) + 1));
    i = -1;
    tmp[i + ft_strlen(&envp[j])] = 0;
    while (str[++i] != '$' && str[i])
        tmp[i] = str[i];
    while (envp[j])
        tmp[i++] = envp[j++];
    tmp[i] = 0;
    free(str);
    return (tmp);
}

void    find_env(char **args, char **envp)
{
    int i;
    int j;
    int c;
    char *str;

    i = -1;
    while (args[++i])
    {
        j = 0;
        c = 0;
        while (args[i][j] != '$' && args[i][j])
            j++;
        if (args[i][j] == '$')
        {
            j++;
            while (envp[c] != NULL && ft_strncmp(envp[c], &args[i][j], ft_strlen(&args[i][j])))
                c++;
            str = change_str(envp[c], args[i]);
            args[i] = str;
        }
    }
}

int red_type(char *str)
{
    int i;
    int j;

    i = -1;
    j = 0;
    while (str[++i] && str[i] != '|' && str[i] != ';')
    {
        if (str[i] == '<' || str[i] == '>')
        {
            j = i;
            if (str[i + 1] == '>' && str[i] == '>')
                i++;
        }
    }
    if (str[j] == '<')
        return (1);
    else if (str[j] == '>')
    {
        if (str[j + 1] == '>')
            return (2);
        return (3);
    }
    return (0);
}