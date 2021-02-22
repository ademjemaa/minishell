/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 20:01:55 by abarbour          #+#    #+#             */
/*   Updated: 2020/08/08 20:12:55 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		valid_var_name_unset(char *var)
{
	int		i;

	if (var && !ft_isalpha(var[0]))
		return (0);
	i = 1;
	while (var[i])
	{
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	unset_env_var(char ***envp, int pos)
{
	int		i;
	char	**new_envp;
	char	***tmp;

	if (!(new_envp = (char **)malloc(sizeof(char *)
	* (str_array_len(*envp)))))
		return ;
	i = 0;
	while ((*envp)[i])
	{
		if (i > pos)
			new_envp[i - 1] = (*envp)[i];
		if (i < pos)
			new_envp[i] = (*envp)[i];
		i++;
	}
	new_envp[i - 1] = NULL;
	tmp = envp;
	free((*envp)[pos]);
	free(*tmp);
	*envp = new_envp;
}

void	remove_var_env(char *var, char ***envp)
{
	int		i;

	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp(var, (*envp)[i], ft_strlen(var)))
		{
			unset_env_var(envp, i);
			return ;
		}
		i++;
	}
}

int		ft_unset(char **args, char ***envp, int p)
{
	int		i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	while (args[i])
	{
		if (valid_var_name_unset(args[i]))
		{
			if (!p)
				remove_var_env(args[i], envp);
		}
		else
		{
			write(2, "Minishell: unset: `", 20);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier", 25);
			write(2, "\n", 1);
			exit_code = p ? 1 : -1;
		}
		i++;
	}
	return (exit_code);
}
