/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 18:49:51 by adjemaa           #+#    #+#             */
/*   Updated: 2020/08/09 23:01:07 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_len(char *str)
{
	int i;
	int total;

	i = 0;
	total = 1;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i = i + 2;
			total = total + 2;
		}
		else if (str[i])
		{
			i++;
			total++;
		}
	}
	return (total);
}

void	init_struct(t_check *c)
{
	c->i = 0;
	c->j = 0;
	c->env = 0;
	c->one = 0;
	c->two = 0;
}

char	*copy_clean(char *tmp, char *str)
{
	t_check c;

	init_struct(&c);
	while (str[c.i])
	{
		if (str[c.i] == '$' && c.two)
			c.env = 1;
		if (c.two == 0)
			c.env = 0;
		while (str[c.i] == '\\' && c.one == 0)
		{
			tmp[c.j] = str[c.i];
			tmp[c.j + 1] = str[c.i + 1];
			c.i = c.i + 2;
			c.j = c.j + 2;
		}
		if ((str[c.i]) && quote_status(&c, &str[c.i]))
		{
			tmp[c.j] = str[c.i];
			c.i++;
			c.j++;
		}
	}
	tmp[c.j] = 0;
	return (tmp);
}

char	*cleaned(char *str)
{
	int		i;
	int		total;
	char	*tmp;

	i = 0;
	total = find_len(str);
	tmp = malloc(sizeof(char) * total);
	if (tmp == NULL)
		return (NULL);
	tmp = copy_clean(tmp, str);
	tmp = rearrange(tmp);
	free(str);
	return (tmp);
}
