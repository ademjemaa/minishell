/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 20:05:41 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/04 22:12:09 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
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
		free_args(tab[i]->args);
		free(tab[i]->args);
		free_files(tab[i]->files);
		free(tab[i]->files);
		free(tab[i]);
		i++;
	}
	free(tab);
}
