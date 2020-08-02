/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mallocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 20:39:14 by adjemaa           #+#    #+#             */
/*   Updated: 2020/08/02 20:56:50 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_arg_tab(char **args, int i, char *line)
{
	int j;

	j = -1;
	while (++j < i)
	{
		free(args[j]);
		j++;
	}
	if (i == 0)
		while (args[++j] != NULL)
			free(args[j]);
	free(args);
	free(line);
	return (NULL);
}
