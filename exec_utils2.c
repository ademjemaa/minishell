/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 23:20:05 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/23 00:00:24 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		rd_files(t_cmd *cmd, int in)
{
	int		i;
	int		fd;

	i = -1;
	fd = -2;
	while (cmd->files[++i].file)
	{
		if (cmd->files[i].red == 1)
			fd = open(cmd->files[i].file, O_RDONLY);
		else
		{
			while (cmd->files[i].file && cmd->files[i].red != 1)
				i++;
			i--;
		}
		if (fd == -1)
		{
			ft_putstr_error(strerror(errno));
			return (-1);
		}
		if (cmd->files[i + 1].file)
			close(fd);
	}
	return (fd == -2 ? in : fd);
}
