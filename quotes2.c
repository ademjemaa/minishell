/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 21:30:15 by adjemaa           #+#    #+#             */
/*   Updated: 2020/06/22 02:10:47 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_red(char *str, int sign)
{
	if (str[0] && ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' 
		&& str[0] <= 'Z') || (str[0] >= '0' && str[0] <= '9') || str[0] == '_'
		|| str[0] == '$' || str[0] == '\\'))
	return (sign);
	else
		return (0);
}

int		find_filered(char *str)
{
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (check_red(&str[2], 1));
		else
			return (check_red(&str[1], 2));
	}
	else if (str[0] == '<')
		return (check_red(&str[1], 3));
	else
		return (-1);
}

char	*file_prot(char *str, char *tmp, int *j)
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
	*j = i + *j;
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
