#include "minishell.h"

int red_type(char *str)
{
    if (str[0] == '<')
        return (1);
    else if (str[0] == '>')
    {
        if (str[1] == '>')
            return (2);
        return (1);
    }
    return (0);
}