/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 18:00:48 by adjemaa           #+#    #+#             */
/*   Updated: 2020/07/17 03:59:23 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     size_counter(char *str)
{
    int i;
    int j;
	char c;

    i = 0;
    j = 0;
    while (str[i])
    {
		while (str[i] == '\\' && str[i + 1])
		{
			i = i + 2;
			j = j + 2;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			j++;
			while (str[i] && str[i] != c)
			{
				i++;
				j++;
			}
		}
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
	int in;
	char c;

    i = 0;
    j = 0;
	in = 0;
    tmp = malloc(sizeof(char) * size_counter(str));
    tmp[size_counter(str) - 1] = 0;
	(void)c;
    while (i < size_counter(str))
    {
		while (str[j] == '\\' && str[j + 1])
		{
			tmp[i++] = str[j++];
			tmp[i++] = str[j++];
		}
		if (str[j] == '\'' || str[j] == '\"')
		{
			if (in == 0)
			{
				c = str[j];
				in = 1;
			}
			else
				in = 0;
		}
        if (((str[j + 1] == '>' && str[j] != '>') || (str[j + 1] == '<')) && str[j] != ' ' && !in)
        {
            tmp[i] = str[j];
            i++;
            tmp[i] = ' ';
        }
		else if ((str[j] == ' ') && (str[j - 1] == '>' || str[j - 1] == '<') && !in)
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
	int c;
    char *tmp;

    j = 0;
	c = 0;
    while (envp != NULL && envp[j] && envp[j] != '=')
        j++;
    j++;
    tmp = malloc(sizeof(char) * (final_size(str, envp)));
    i = -1;
    while (str[++i] && str[i] != '$')
	{
		if (str[i] == '\\')
		{
        	tmp[c] = str[i];
			i++;
			c++;
		}
		tmp[c] = str[i];
		c++;
	}
    while (envp != NULL && envp[j])
        tmp[c++] = envp[j++];
	i++;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
		i++;
	while (str[i])
	{
		tmp[c] = str[i];
		c++;
		i++;
	}
    tmp[c] = 0;
    free(str);
    return (tmp);
}

void    find_env(char **args, char **envp)
{
    int i;
    int j;

    i = -1;
	if (args == NULL)
		return ;
    while (args[++i] != NULL)
    {
		j = 0;
		if (args[i][0] != '\'')
		{
			while (args[i][j])
			{
				if (args[i][j] == '\\')
					j = j + 2;
				if (args[i][j] == '$')
				{
					args[i] = swap_case(args[i], envp, j + 1);
					j = 0;
				}
				else
					j++;
			}
		}
	}
}

int red_type(char *str)
{
	int i;
	int one;
	int two;
	int ret;

	i = -1;
	one = 0;
	two = 0;
	ret = 0;
	while (str[++i])
	{
		while (str[i] == '\\' && one == 0)
			i = i + 2;
		if (str[i] == '\'' && !two)
			one = !one;
		if (str[i] == '\"' && !one)
			two = !two;
		if ((str[i] == '>' || str[i] == '<') && one == 0 && two == 0)
			ret = find_filered(&str[i]);
		if (ret > 0)
			break;
	}
	if (one || two)
		ret = -1;
	return (ret);
}
