/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 19:30:41 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/31 16:52:50 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		valid_var_name(char *var)
{
	int		i;

	if (var && !ft_isalpha(var[0]))
		return (0);
	i = 1;
	while (var[i])
	{
		if (var[i] == '=')
			return (1);
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int		equal_pos(char *var)
{
	int		i;

	i = 0;
	while(var[i])
	{
		if (var[i] == '=')
			break;
		i++;
	}
	return (i);
}

void	add_var_to_env(char *var, char ***envp)
{
	int		i;

	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp(var, (*envp)[i], equal_pos(var)))
		{
			update_env(var, *envp, i);
			return;
		}
		i++;
	}
	add_env(var, envp);
}

int		ft_export(char *path, char **args, char ***envp)
{
	int		i;

	i = 1;
	while (args[i])
	{
		if (valid_var_name(args[i]))
			add_var_to_env(args[i], envp);
		else
		{
			write(2, "Minishell: export: `", 20);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier", 25);
			write(2, "\n", 1);
		}
		i++;
	}
	return (0);	
}
