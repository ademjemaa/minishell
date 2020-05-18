#include "minishell.h"

int total_args(char **args)
{
    int i;
    int j;
    int total;
    char c;

    i = 0;
    total = 1;
    while (args[i] != NULL)
    {
        j = 0;
        while (args[i][j])
        {
            if (args[i][j] == '\'' || args[i][j] == '\"')
            {
                c = args[i][j];
                while (args[i][j])
                {
                    
                }
                
            }

    }
    
}