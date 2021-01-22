/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_name_proces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 13:25:35 by adjemaa           #+#    #+#             */
/*   Updated: 2020/08/09 14:58:52 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		nb_remove_sq(char *line, int *i)
{
	int		nb_c;

	nb_c = 0;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
	{
		if (line[*i + 1])
			nb_c++;
		(*i)++;
	}
	(*i)++;
	return (nb_c);
}

int		nb_remove_dq(char *line, int *i)
{
	int		nb_c;

	nb_c = 0;
	(*i)++;
	while (line[*i] && line[*i] != '\"')
	{
		if (line[*i] == '\\' && (line[*i + 1] == '\\' /*|| line[*i + 1] == '$'*/
			|| line[*i + 1] == '\"'))
			(*i)++;
		if (line[*i + 1])
			nb_c++;
		(*i)++;
	}
	(*i)++;
	return (nb_c);
}

int		fill_dq_sq(char *line, char *str, int *i, int *j)
{
	if (line[*i] == '\'')
	{
		while (line[++(*i)] && line[*i] != '\'')
			if (line[*i + 1])
				str[(*j)++] = line[*i];
		(*i)++;
		return (1);
	}
	else if (line[*i] == '\"')
	{
		while (line[++(*i)] && line[*i] != '\"')
		{
			if (line[*i] == '\\' && (line[*i + 1] == '\\' || line[*i + 1] == '$'
				|| line[*i + 1] == '\"'))
				(*i)++;
			if (line[*i + 1])
				str[(*j)++] = line[*i];
		}
		(*i)++;
		return (1);
	}
	return (0);
}

char	*create_cmd_name(char *line, int nb_c)
{
	char	*str;
	int		i;
	int		j;

	if (!(str = malloc(nb_c + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (!fill_dq_sq(line, str, &i, &j) && line[i])
			str[j++] = line[i++];
	}
	str[j] = '\0';
	return (str);
}
