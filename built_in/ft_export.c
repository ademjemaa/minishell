/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 19:30:41 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/27 00:19:34 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		valid_var_name(char *var)
{
	return (0);
}

void	add_var_to_env(char *var, char ***envp)
{

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
