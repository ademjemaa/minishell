#include "minishell.h"

char    *str_find(char *line)
{
    int     i;
    int     j;
    char    *str;

    i = 0;
    while (!(line[i] == '|' || line[i] == ';' || line[i] == '\0'))
        i++;
    str = malloc(sizeof(char) * (i + 1));
    str[i] = 0;
    j = -1;
    while (++j < i)
        str[j] = line[j];
    return (str);
}

void    args_parser(char *path, char *str, char **envp, t_cmd *stru)
{
    char    **args;
    char    *tmp;
    int     i;

    tmp = str_find(str);
    tmp = rearrange(tmp);
    args = ft_split(tmp, ' ');
    stru->files = find_filelst(args);
    stru->args = find_path(args, stru, envp);
    free (tmp);
    if (!stru->args[0] || !path)
    {
        free(stru->args);
        return ;
    }
    i = -1;
    while (stru->args[++i] != NULL)
    {
        if (stru->args[i][0] == '\"' || stru->args[i][0] == '\'')
        {
            tmp = stru->args[i];
            if (stru->args[i][0] == '\"')
                stru->args[i] = ft_strtrim(stru->args[i], "\"");
            if (stru->args[i][0] == '\'')
                stru->args[i] = ft_strtrim(stru->args[i], "\'");
            free(tmp);
        }
    }
    free_all(args);
    find_env(stru->args, envp);
}

int find_file(char *str)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (str[j] && (str[j] == '>' || str[j] == ' ' || str[j] == '<'))
        j++;
    while (str[j] != ' ' && str[j] != 0 && str[j] != '|' && str[j] != '>'
            && str[j] != '<' && str[j] != ';')
    {
        i++;
        j++;
    }
    return (i);
}

char    *file_name(char *str, t_cmd *struc)
{
    int i;
    char *tmp;

    i = 0;
    struc->red = red_type(str);
    while (struc->files && struc->files[i] != NULL)
        i++;
    tmp = ft_strdup(struc->files[i]);
    return (tmp);
}

int     sep_parser(char *str, t_cmd *tmp)
{
    int i;

    i = 0;
    tmp->red = -1;
    while (str[i] != 0 && str[i] != '|' && str[i] != '>'
            && str[i] != '<' && str[i] != ';')
        i++;
    if (str[i] == '>' || str[i] == '<')
        tmp->file = file_name(&str[i], tmp);
    while (str[i] != 0 && str[i] != '|' && str[i] != ';')
        i++;
    if (str[i] == ';')
        return (5);
    else if (str[i] == '|')
        return (4);
    else if (str[i] == 0)
        return (0);
    else
        return (-1);
}

int check_name(char *line, t_cmd *tmp)
{
    int     ret;
    char    *str;

    ret = 0;
    str = cmd_name(line);
    if (!ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2) ||
        !ft_strncmp(str, "export", 6) || !ft_strncmp(str, "unset", 5) || !ft_strncmp(str, "env", 3) ||
        !ft_strncmp(str, "exit", 4))
    {
        ret = 1;
        tmp->built = 1;
    }
    else
        tmp->built = 0;
    free(str);
    return ret;
}