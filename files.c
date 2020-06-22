#include "minishell.h"

void    free_all(char **args)
{
    int i;
    
    i = 0;
    while (args[i] != NULL)
    {
        free(args[i]);
        i++;
    }
    free(args);
}

char     **total_args(char **args, char *str)
{
    int i;
    int total;
    char    **fill;

    i = 0;
    total = 1;
    while (args[i] != NULL)
    {
        if (args[i][0] != '<' && args[i][0] != '>')
            total++;
        i++;
    }
    fill = (char **)malloc(sizeof(char *) * total);
    fill[i] = NULL;
    if (total > 1)
	{
		if (str != NULL)
        	fill[0] = ft_strdup(str);
		else
			fill[0] = NULL;
	}
    return (fill);
}

char    **find_path(char **args, t_cmd *tmp, char **envp)
{
    int i;
    int j;
    char    **fill;

    i = 0;

    while (args[i] && (args[i][0] == '<' || args[i][0] == '>'))
        i++;
    tmp->path = path_parser(args[i], envp, tmp);
    fill = total_args(args, tmp->path);
    j = 1;
    while (args[i + 1] != NULL)
    {
        i++;
        if (args[i][0] != '>' && args[i][0] != '<')
        {
            fill[j] = ft_strdup(args[i]);
            j++;
        }
    }
	free_all(args);
	fill[j] = NULL;
    return (fill);
}

int     file_counter(char **args)
{
    int i;
    int total;

    total = 0;
    i = 0;
    while (args[i] != NULL)
    {
        if (args[i][0] == '<' || args[i][0] == '>')
            total++;
        i++;
    }
    return (total + 1);
}

t_filelst	*find_filelst(char **args, char **envp)
{
    int i;
    int j;
    t_filelst    *files;

    i = -1;
    j = 0;
    files = (t_filelst *)malloc(sizeof(t_filelst*) * file_counter(args));
    files[file_counter(args).file - 1] = NULL;
    while (args[++i] != NULL)
    {
        if (args[i][0] == '<' || args[i][0] == '>')
        {
			files.red = find_filered(args[i]);
            if (args[i][1] == '>')
                files.file[j] = retrieve(&args[i][2], envp);
            else
                files.file[j] = retrieve(&args[i][1], envp);
            j++;
        }
    }
    return (files);
}
