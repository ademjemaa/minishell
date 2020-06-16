/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 21:20:08 by abarbour          #+#    #+#             */
/*   Updated: 2020/06/17 00:18:51 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	proc_args(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->args[i])
	{
		if (args[i][0] == "\"")
		{
			tmp = args[i];
			args[i] = remove_dq(args[i]);
			free(tmp);
		}
		else if (args[i][0] == "\'")
		{
			tmp = args[i];
			args = remove_sq(args[i]);
			free(tmp);
		}
	}
}
