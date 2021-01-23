/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:08:21 by adjemaa           #+#    #+#             */
/*   Updated: 2021/01/23 13:18:25 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	looper_env(char **args, int *i, int *j, char **envp)
{
	*j = 0;
	if (args[*i][*j] == '\'')
	{
		*j = *j + 1;
		while (args[*i][*j] && args[*i][*j] != '\'')
			*j = *j + 1;
		*j = *j + 1;
	}
	while (args[*i][*j])
	{
		if (args[*i][*j] == '\\')
			*j = *j + 2;
		else if (args[*i][*j] == '$' && args[*i][*j + 1] != '\"')
		{
			args[*i] = swap_case(args[*i], envp, *j + 1);
			*j = 0;
		}
		else
			*j = *j + 1;
	}
}
