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

void    args_parser(char *str, char **envp, t_cmd *stru)
{
    char    **args;
    char    *tmp;

    tmp = str_find(str);
	printf("command string found\n");
	tmp = cleaned(tmp);
	printf("cleaning done, new string = #%s\n", tmp);
	args = first_split(tmp);
	stru->files = NULL;
	stru->file = NULL;
    stru->files = find_filelst(args, envp);
	printf("files done\n");
    stru->args = find_path(args, stru, envp);
	printf("path || args done\n");
	free(tmp);
//    free_all(args);
   	find_env(stru->args, envp);
	printf("env done\n");
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
    while (struc->files && struc->files[i].file != NULL)
        i++;
    i--;
    tmp = ft_strdup(struc->files[i].file);
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
	tmp->built = 0;
    str = cmd_name(line);
	if (str != NULL)
	{
/*    if (!ft_strcmp(str, "echo") || */ if (!ft_strcmp(str, "cd") ||
        !ft_strcmp(str, "export") || !ft_strcmp(str, "unset") || !ft_strcmp(str, "env") ||
        !ft_strcmp(str, "exit"))
    	{
    	    ret = 1;
    	    tmp->built = 1;
    	}
	}
    else
        tmp->built = 0;
    free(str);
    return ret;
}
