/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:04:45 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/25 18:46:02 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_echo(char *path, char **args, char **envp)
{
	int		i;
	int		j;
	int		nl;

	i = 1;
	nl = 1;
	while (args[i])
	{
		if (i == 1 && !ft_strncmp(args[i], "-n", 3))
		{
			nl = 0;
			while (args[i] && !ft_strncmp(args[i], "-n", 3))
				i++;
		}
		j = -1;
		while (args[i][++j])
			write(1, args[i] + j, 1);
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (nl)
		write(1, "\n", 1);
	exit(0);
}
