/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:03:08 by abarbour          #+#    #+#             */
/*   Updated: 2021/01/23 13:37:08 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		str_length_after_trait(char *str)
{
	int		i;
	int		nb;

	i = -1;
	nb = 0;
	while (str[++i])
	{
		if (str[i] == '\\' || str[i] == '$')
			nb += 2;
		else
			nb++;
	}
	return (nb);
}

char	*trait_after_export(char **str)
{
	char	*s;
	int		i;
	int		nb;

	s = (char *)malloc(sizeof(char) * str_length_after_trait(*str) + 1);
	nb = 0;
	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '\\' || (*str)[i] == '$')
		{
			s[nb++] = '\\';
			s[nb++] = (*str)[i];
		}
		else
			s[nb++] = (*str)[i];
	}
	s[nb] = 0;
	free(*str);
	*str = s;
	return (*str);
}
