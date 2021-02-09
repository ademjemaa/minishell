/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 20:05:41 by abarbour          #+#    #+#             */
/*   Updated: 2021/01/30 16:27:49 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args, int total)
{
	int		i;

	i = 0;
	while (i < total)
	{
		if (args[i])
			free(args[i]);
		i++;
	}
}

void	free_files(t_filelst *files)
{
	int		i;

	i = 0;
	while (files[i].file)
	{
		free(files[i].file);
		i++;
	}
}

void	free_cmds(t_cmd **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]->path);
		free(tab[i]->file);
		free_args(tab[i]->args, tab[i]->total);
		free(tab[i]->args);
		free_files(tab[i]->files);
		free(tab[i]->files);
		free(tab[i]);
		i++;
	}
	free(tab);
}
