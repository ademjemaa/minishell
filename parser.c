#include "minishell.h"

int counter(char *line)
{
    int total;
    int i;

    total = 1;
    while(line[i])
    {
        if (line[i] == '|' ||  line[i] == ';' )
            total++;
        i++;
    }
    return (total);
}

char    *cmd_name(char *line)
{
    int i;
    int j;
    char *str;

    j = 0;
    while (line[j] == ' ')
        j++;
    i = j;
    while (line[i] && line[i] != ' ')
        i++;
    str = malloc(sizeof(char) * (i - j + 1));
    str[i - j] = '\0';
    i = 0;
    while (line[j] != ' ' && line[j])
        str[i++] = line[j++];
    return (str);
}

char    *path_parser(char *line, char **envp)
{
    int i;
    char **str;
    struct stat sb;


    i = 0;
    if (check_name(line))
        return (cmd_name(line));
    while (ft_strncmp(envp[i], "PATH=", 5))
        i++;
    str = ft_split(envp[i], ':');
    i = 0;
    while (str[i] != NULL)
    {
        if (str[i][ft_strlen(str[i]) - 1] != '/')
            str[i] = ft_strjoinfree(str[i], "/", 1);
        str[i] = ft_strjoinfree(str[i], cmd_name(line), 3);
        i++;
    }
    i = 0;
    //**str fi e5er case lezemou NULL ema huwa ki youssil el e5er case yaamel segfault
    while (((stat(str[i], &sb)) != 0) && (str[i] != NULL))
        i++;
    return (str[i]);
}

t_cmd   *params(char *line, char **envp)
{
    t_cmd *tmp;

    envp = envp;
    tmp = (t_cmd*)malloc(sizeof(t_cmd));
    //lehi ysegfaulti lehna 5ater j-2 ki tabda el j a9al men 2
    tmp->sep =  sep_parser(line, tmp);
    tmp->path = path_parser(line, envp);
    tmp->args = args_parser(tmp->path, line);
    int i;
    i = 0;
    while (tmp->args[i] != NULL)
    {
        printf("%s\n", tmp->args[i]);
        i++;
    }
    printf("%s file %s sep %d red %d\n", tmp->path, tmp->file, tmp->sep, tmp->red);
    return (tmp);
}

t_cmd **parser(char *line, char **envp)
{
    int total;
    t_cmd **tab;
    int i;
    int j;

    i = 0;
    total = counter(line);
    j = 0;
	tab = (t_cmd**)malloc(sizeof(t_cmd**) * (total + 1));//lahna zedet el + 1 lazem yofa b null
    while (line[j])
    {
        tab[i] = params(line, envp);
        i++;
        while (line[j] && line[i] != '|' && line[j] != ';')
            j++;
    }
    tab[i] = NULL;// w lahna hattet el null
    return (tab);
}