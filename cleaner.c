/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 18:49:51 by adjemaa           #+#    #+#             */
/*   Updated: 2020/05/28 18:57:52 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_len(char *str)
{
	int i;
	int total;
	int one;
	int two;

	i = 0;
	total = 1;
	one = 0;
	two = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && one == 0)
		{
			i = i + 2;
			total = total + 2;
		}
		if ((str[i] == '\"' && str[i + 1] == '\"' && two == 0) || (str[i] == '\'' && str[i + 1] == '\'' && one == 0))
			i = i + 2;
		else if (str[i])
		{
			i++;
			total++;
		}
	}
	return (total);
}

void	check_final(int i, int j,char  *tmp)
{
	char	*str;

	str = ft_strdup(tmp);
	if (i != j)
		tmp = copy_clean(tmp, str);
}

char	*copy_clean(char *tmp, char *str)
{
	int i;
	int j;
	int	one;
	int two;

	i = 0;
	j = 0;
	one = 0;
	two = 0;
	while (str[i])
	{
		if (str[i] == '\\' && one == 0)
		{
			tmp[j] = str[i];
			tmp[j + 1] = str[i + 1];
			i = i + 2;
			j = j + 2;
		}
		if ((str[i]) && quote_status(&one, &two, &i, &str[i]))
		{
			tmp[j] = str[i];
			i++;
			j++;
		}
		if (str[i] == 0 && (one == 1 || two == 1))
		{
			printf("quotation error fix me later one == %d two == %d\n", one, two);
			return (NULL);;
		}
	}
	tmp[j] = 0;
	return (tmp);
}

char	*cleaned(char *str)
{
	int 	i;
	int 	total;
	char	*tmp;

	i = 0;
	total = find_len(str);
	tmp = malloc(sizeof(char) * total);
	tmp = copy_clean(tmp, str);
	tmp = rearrange(tmp);
	return (tmp);
}
