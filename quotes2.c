/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 21:30:15 by adjemaa           #+#    #+#             */
/*   Updated: 2020/08/09 12:49:09 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_slash(char *tmp, char *str, t_check *c)
{
	tmp[c->j] = str[c->i];
	c->j++;
	c->i++;
	tmp[c->j] = str[c->i];
	c->j++;
	c->i++;
}

int		check_red(char *str, int sign)
{
	if (str[0] && ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A'
		&& str[0] <= 'Z') || (str[0] >= '0' && str[0] <= '9') || str[0] == '_'
		|| str[0] == '$' || str[0] == '\\' || str[0] == '\'' ||
		str[0] == '\"'))
		return (sign);
	else
		return (-1);
}

int		find_filered(char *str)
{
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (check_red(&str[2], 2));
		else
			return (check_red(&str[1], 3));
	}
	else if (str[0] == '<')
		return (check_red(&str[1], 1));
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
			break ;
		i++;
	}
	*j = i + *j;
	tmp[i] = 0;
	return (tmp);
}

int		line_return(char *str)
{
	t_check	c;

	init_struct(&c);
	while (str[c.i])
	{
		while (str[c.i] == '\\')
			c.i = c.i + 2;
		if (str[c.i] == '\'' && c.two == 0)
			c.one = !(c.one);
		else if (str[c.i] == '\"' && c.one == 0)
			(c.two) = !(c.two);
		if (str[c.i] == ' ' && !(c.two) && !(c.one))
			break ;
		c.i++;
	}
	return (c.i);
}
