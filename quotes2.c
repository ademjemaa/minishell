/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 21:30:15 by adjemaa           #+#    #+#             */
/*   Updated: 2020/06/08 21:57:30 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*file_prot(char *str, char *tmp)
{
	int i;
	int one;
	int two;

	one = 0;
	two = 0;
	i = 0;
	while (str[i])
	{
		tmp[i] = str[i];
		if (str[i] == '\'' && two == 0 && str[i - 1] != '\\')
			one = !one;
		if (str[i] == '\"' && one == 0 && str[i - 1] != '\\')
			two = !two;
		if (str[i] == ' ' && str[i - 1] != '\\' && one == 0 && two == 0)
			break;
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

int		line_return(char *str)
{
	int i;
	int one;
	int two;

	i = 0;
	one = 0;
	two = 0;
	while (str[i])
	{
		while (str[i] == '\\')
			i = i + 2;
		if (str[i] == '\'' && two == 0)
			one = !one;
		else if (str[i] == '\"' && one == 0)
			two = !two;
		if (str[i] == ' ' && !two && !one)
			break;
		i++;
	}
	return (i);
}
