/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 21:14:08 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/26 23:28:55 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		str_array_len(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	*free_env(char **env, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		free(env[j]);
		i++;
	}
	free(env);
	return (NULL);
}

char	**env_start(char **envp)
{
	int		i;
	int		j;
	char	**env;

	if (!(env = (char **)malloc(sizeof(char *) * (str_array_len(envp) + 1))))
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (!(env[i] = (char *)malloc(ft_strlen(envp[i]) + 1)))
			return ((char **)free_env(env, i));
		j = 0;
		while (envp[i][j])
		{
			env[i][j] = envp[i][j];
			j++;
		}
		env[i][j] = '\0';
		i++;
	}
	env[i] = NULL;
	return (env);
}
