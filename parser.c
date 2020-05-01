#include "minishell.h"

int counter(char *line)
{
    int total;
    int i;

    total = 1;
    while(line[i])
    {
        if (line[i] == '|' || line[i] == '>' || line[i] == '<' || line[i] == ';' )
            if (total++ && line[i + 1] == '>' && line[i] == '>')
                i++;
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

t_cmd   *params(char *line, int i, char **envp)
{
    int j;
    int c;
    t_cmd *tmp;

    c = 0;
    j = 0;
    envp = envp;
    tmp = (t_cmd*)malloc(sizeof(t_cmd));
    while (c < i && line[j])
    {
        if (line[j] == '|' || line[j] == '>' || line[j] == '<' || line[j] == ';' )
            if (++c && line[j + 1] == '>' && line[j] == '>')
                j++;
        j++;
    }
    //lehi ysegfaulti lehna 5ater j-2 ki tabda el j a9al men 2
    if (j > 1)
        tmp->sep =  sep_parser(&line[j - 2]);
    else
    {
        tmp->sep = -1;
    }
    tmp->path = path_parser(&line[j], envp);
    tmp->args = args_parser(tmp->path, &line[j]);
    return (tmp);
}

t_cmd **parser(char *line, char **envp)
{
    int total;
    t_cmd **tab;
    int i;

    i = 0;
    total = counter(line);
	tab = (t_cmd**)malloc(sizeof(t_cmd**) * (total + 1));//lahna zedet el + 1 lazem yofa b null
    while (i < total)
    {
        tab[i] = params(line, i, envp);
        i++;
    }
    tab[i] = NULL;// w lahna hattet el null
    return (tab);
}