/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:05:56 by adjemaa           #+#    #+#             */
/*   Updated: 2020/05/27 18:12:23 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		quote_status(int *one, int *two, int *i, char *str)
{
	printf("current = %s\n", str);
	if (str[0] == '\"' && str[1] != '\"' && !(*one))
		*two = !(*two);
	else if (str[0] == '\'' && str[1] != '\'' && !(*two))
		*one = !(*one);
	else if (str[0] == '\"' && str[1] == '\"' && !(*one))
	{
		*i = *i + 2;
		return (0);
	}
	else if (str[0] == '\'' && str[1] == '\'' && !(*two))
	{
		*i = *i + 2;
		return (0);
	}
	return (1);
}
