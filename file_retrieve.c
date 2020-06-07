/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_retrieve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 18:38:18 by adjemaa           #+#    #+#             */
/*   Updated: 2020/06/07 21:30:08 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		envp_len(char *str, char *tmp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tmp[j])
		j++;
	while (str[i])
	{
		if (str[i] == '=')
			break;
		i++;
	}
	if (j > i)
		i = j;
	return (i);
}

int		env_tran_len(char *str, char **envp, int *i)
{
	int c;
	int j;
	char *tmp;

	c = 0;
	j = 0;
	tmp = exact_env(str);
	while (envp[c] != NULL  && ft_strncmp(envp[c], tmp, envp_len(envp[c], tmp)))
		c++;
	while (str[*i] && ((str[*i] >= 'a' && str[*i] <= 'z') || (str[*i] >= 'A' && str[*i] <= 'Z') || (str[*i] >= '0' && str[*i] <= '9') || str[*i] == '_'))
		*i = *i + 1;
	if (envp[c] != NULL)
	{
		while (envp[c][j] != '=')
			j++;
		return (ft_strlen(envp[c]) - j - 2);
	}
	return (0);
}

int		file_len(char *str, char **envp)
{
	int i;
	int total;
	int one;
	int two;

	total = 1;
	i = 0;
	one = 0;
	two = 0;
	printf("str == %s\n", str);
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\'' && str[i - 1] != '\\' && !two)
		{
			one = !one;
			total--;
		}
		if (str[i] == '\"' && str[i - 1] != '\\' && !one)
		{
			two = !two;
			total--;
		}
		if (str[i] == '$' && one == 0 && str[i - 1] != '\\')
			total = total + env_tran_len(&str[i + 1], envp, &i);
		total++;
		i++;
	}
	printf("total == %d\n", total);
	return (total);
}

char	*retrieve(char *str, char **envp)
{
	char *tmp;
	int i;


	i = 0;
	printf("line %s\n", str);
	tmp = malloc(sizeof(char *) * file_len(str, envp));
	while (str[i])
		i++;
	return (tmp);
}
