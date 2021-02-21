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

void	find_spaces(t_cmd *stru)
{
	int i;
	int j;

	i = -1;
	while (++i < stru->total)
	{
		j = 0;
		while (stru->args[i][j] == ' ')
			j++;
		if (stru->args[i][j] == 0)
			ft_bzero(stru->args[i], ft_strlen(stru->args[i]));
	}
}
