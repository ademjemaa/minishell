/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_retrieve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 18:38:18 by adjemaa           #+#    #+#             */
/*   Updated: 2020/06/02 21:31:51 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		envp_len(char *str, char *tmp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tmp[j])
		j++;
	while (str[i])
	{
		if (str[i] == '=')
			break;
		i++;
	}
	if (j > i)
		i = j;
	return (i);
}

char	*retrieve(char *str)
{
	char *tmp;
	(void)str;
	tmp = 0;
	return (tmp);
}
