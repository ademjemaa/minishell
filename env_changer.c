/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_changer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 01:48:21 by adjemaa           #+#    #+#             */
/*   Updated: 2020/07/17 02:25:51 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_code(char *tmp, char *args, int j)
{
	int 	i;
	char	*str;

	str = malloc(sizeof(char) * j + ft_strlen(tmp) + 1);
	i = 0;
	while (i < j - 1)
	{
		str[i] = args[i];
		i++;
	}
	j = 0;
	while (tmp[j])
	{
		str[i] = tmp[j];
		i++;
		j++;
	}
	str[i] = 0;
	free(tmp);
	free(args);
	return (str);
}

char	*swap_case(char *args, char **envp, int j)
{
	char	*tmp;
	int 	c;

	c = 0;
	if (args[j] == '?')
	{
		tmp = ft_itoa(exit_code);
		tmp = ft_strjoinfree(tmp, &args[j + 1], 1);
		tmp = change_code(tmp, args, j);
	}
	else
	{
		tmp = exact_env(&args[j]);
		while (envp[c] != NULL && ft_strncmp(envp[c], tmp, envp_len(envp[c], tmp)))
			c++;
		free(tmp);
		tmp = change_str(envp[c], args);
	}
	return (tmp);
}
