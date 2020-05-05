#include "minishell.h"

char    *str_find(char *line)
{
    int     i;
    int     j;
    char    *str;

    i = 0;
    while (!(line[i] == '|' || line[i] == '>' || line[i] == '<' || line[i] == ';' || line[i] == '\0'))
        i++;
    str = malloc(sizeof(char) * (i + 1));
    str[i] = 0;
    j = -1;
    while (++j < i)
        str[j] = line[j];
    return (str);
}

char    **args_parser(char *path, char *str)
{
    char    **args;
    char    *tmp;
    int     i;

    tmp = str_find(str);
    args = ft_split(tmp, ' ');
    free (tmp);
    if (!args[0] || !path)
    {
        free(args);
        return (NULL);
    }
    i = -1;
    tmp = args[0];
    args[0] = ft_strdup(path);
    free (tmp);
    while (args[++i] != NULL)
    {
        if (args[i][0] == '\"' || args[i][0] == '\'')
        {
            tmp = args[i];
            if (args[i][0] == '\"')
                args[i] = ft_strtrim(args[i], "\"");
            if (args[i][0] == '\'')
                args[i] = ft_strtrim(args[i], "\'");
            free(tmp);
        }
    }
    return (args);
}

int find_file(char *str)
{
    int i;

    i = 1;
    while (str[i] != ' ' && str[i] != 0 && str[i] != '|' && str[i] != '>'
            && str[i] != '<' && str[i] != ';')
        i++;
    return (i);
}

char    *file_name(char *str)
{
    int i;
    int j;
    char *tmp;

    i = 1;
    while (str[i] == ' ')
        i++;
    j = 0;
    tmp = malloc(sizeof(char) * (find_file(&str[i])));
    tmp[find_file(&str[i]) - 1] = 0;
    while (str[i] != ' ' && str[i] != 0 && str[i] != '|' && str[i] != '>'
            && str[i] != '<' && str[i] != ';')
        tmp[j++] = str[i++];
    return (tmp);
}

int     sep_parser(char *str, t_cmd *tmp)
{
    int i;

    i = 0;
    while (str[i] != 0 && str[i] != '|' && str[i] != '>'
            && str[i] != '<' && str[i] != ';')
        i++;
    if (str[i] == 0)// Amine : el if hethi kanet ellota 7attetha lehna 5atrou ysegfaulti kan ma fammach sep lazem melloul yo5rej
        return (0);
    if (str[i] == ';')
        return (5);
    else if (str[i] == '>' || str[i] == '<')
    {
         tmp->file = file_name(&str[i]);
        if (str[i + 1] == '>')
            return (1);
        else if (str[i] == '<')// Amine : lehna kont 7atet str[1] raddetha str[i] logique akther
            return (3);
        return (2);
    }
    else if (str[i] == '|')// Amine : kifkif lehna str[i]
        return (4);
    else
        return (-1);
}

int check_name(char *line)
{
    int     ret;
    char    *str;

    ret = 0;
    str = cmd_name(line);
    if (!ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2) ||
        !ft_strncmp(str, "export", 6) || !ft_strncmp(str, "unset", 5) || !ft_strncmp(str, "env", 3) ||
        !ft_strncmp(str, "exit", 4))
        ret = 1;
    free(str);
    return ret;
}