#include "minishell.h"

int counter(char *line)
{
    int total;
    int i;

    total = 1;
	i = 0;
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
	printf("line == %s\n", line);
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
	str[i] = 0;
	printf("str == %s\n", str);
    return (str);
}

char    *path_parser(char *line, char **envp, t_cmd *tmp)
{
    int i;
    char **str;
	char *ret;
    struct stat sb;

    i = 0;
    if (check_name(line, tmp))
        return (cmd_name(line));
    while (ft_strncmp(envp[i], "PATH=", 5))
        i++;
    str = ft_split(envp[i], ':');
    i = -1;
    while (str[++i] != NULL)
    {
        if (str[i][ft_strlen(str[i]) - 1] != '/')
            str[i] = ft_strjoinfree(str[i], "/", 1);
        str[i] = ft_strjoinfree(str[i], cmd_name(line), 3);
    }
    i = 0;
	//boucle mouch 9a3da tou9if ki str[i] == NULL w timchi taamel check lil stat ye5i issir  segfault
	while (str[i] != NULL)
	{
		printf("str == %s\n", str[i]);
		if (stat(str[i], &sb) == 0)
			break;
        i++;
	}
	printf("%d\n", i);
	if (str[i] != NULL)
		ret = ft_strdup(str[i]);
	else
		ret = NULL;
	free_all(str);
    return (ret);
}

void    print_structure(t_cmd *tmp)
{
    int i;

    i = 0;
    printf("path == %s\nfile == %s\n", tmp->path, tmp->file);
    while (tmp->args[i] != NULL)
    {
        printf("args == %s\n", tmp->args[i]);
        i++;
    }
    i = 0;
    while (tmp->files[i] != NULL)
    {
        printf("files == %s\n", tmp->files[i]);
        i++;
    }
    printf("sep == %d\nred == %d\nbuild == %d\n", tmp->sep, tmp->red, tmp->built);
}

t_cmd   *params(char *line, char **envp)
{
    t_cmd *tmp;

    tmp = (t_cmd*)malloc(sizeof(t_cmd));
    args_parser(line, envp, tmp);
    tmp->sep =  sep_parser(line, tmp);
    print_structure(tmp);
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
        tab[i] = params(&line[j], envp);
        i++;
        while (line[j] && line[i] != '|' && line[j] != ';')
            j++;
    }
    tab[i] = NULL;// w lahna hattet el null
    return (tab);
}
