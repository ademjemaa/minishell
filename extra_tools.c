/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:20:26 by adjemaa           #+#    #+#             */
/*   Updated: 2021/02/21 15:55:33 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_end_space(t_cmd *stru, int i)
{
	if (stru->args[i][ft_strlen(stru->args[i]) - 2] != '\\')
	{
		while (i < stru->total && stru->args[i])
		{
			if (stru->args[i][0] != 0)
				break;
			i++;
		}
		printf("i == %d total == %d, args == %s\n\n", i, stru->total, stru->args[i]);
		if (i == stru->total)
			return (1);
	}
	return (0);
}

void	find_spaces(t_cmd *stru)
{
	int i;
	int j;

	i = 0;
	while (stru->args && stru->args[i] && i < stru->total)
	{
		j = 0;
		while (stru->args[i][j] == ' ')
			j++;
		if (stru->args[i][j] == 0)
			ft_bzero(stru->args[i], ft_strlen(stru->args[i]));
		i++;
	}
/*	i = 0;
	while (stru->args && stru->args[i] && i < stru->total)
	{
		if (stru->args[i][ft_strlen(stru->args[i]) - 1] == ' ')
			if (check_end_space(stru, i))
			{
				printf("allahou\n");
				stru->args[i][ft_strlen(stru->args[i]) - 1] = 0;
				printf("akbar\n");
			}
		i++;
	}*/
}
