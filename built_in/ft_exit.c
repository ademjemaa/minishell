/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 00:32:11 by abarbour          #+#    #+#             */
/*   Updated: 2020/08/23 20:56:58 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_exit(char **args)
{
	int				j;
	unsigned char	code;

	j = 0;
	if (!args[1])
		exit(0);
	while (args[1][j] && ft_isdigit(args[1][j]))
		j++;
	if (args[1][j])
	{
		write(1, "minishell: exit: ", 17);
		write(1, args[1], ft_strlen(args[1]));
		write(1, ": numeric argument required\n", 28);
		exit(255);
	}
	if (args[1] && args[2])
	{
		write(1, "minishell: exit: too many arguments\n", 36);
		return (-1);
	}
	code = ft_atoi(args[1]);
	g_exit_code = (int)code;
	exit(g_exit_code);
}
