/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:59:38 by abarbour          #+#    #+#             */
/*   Updated: 2020/06/21 21:36:36 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		narg_len_dq(char *arg)
{
	int		i;
	int		j;

	if (arg[0] != '"')
		return (0);//lazem gestion d'erreur
	i = 1;
	j = ft_strlen(arg) - 2;
	while (arg[i])
	{
		if (arg[i] == '\\' && (arg[i + 1] == '\\' || arg[i + 1] == '$'))
		{
			j--;
			i++;
		}
		i++;
	}
	if (arg[i - 1] != '"')
		return (0);//lazem gestion d'erreur
	return (j);
}

int		narg_len_sq(char *arg)
{
	int		i;
	int		j;

	if (arg[0] != '\'')
		return (0);//lazem gestion d'erreur
	i = 1;
	j = ft_strlen(arg) - 2;
	while (arg[i])
		i++;
	if (arg[i - 1] != '\'')
		return (0);//lazem gestion d'erreur
	return (j);
}

int		nargs_count(char **args)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (args[i])
	{
		while (args[i] && (args[i][0] == '"' || args[i][0] == '\'')
			&& args[i][ft_strlen(args[i]) - 1] != ' ')
			i++;
		j++;
		if (args[i])
			i++;
	}
	return (j);
}

int		cr_files(t_cmd *cmd)
{
	int		i;
	int		fd;

	i = 0;
	while (cmd->files[i])
	{
		fd = open(cmd->files[i], O_WRONLY | O_CREAT);
		if (cmd->files[i + 1])
			close(fd);
		i++;
	}
	printf("hiiiiii\n");
	return (fd);
}
