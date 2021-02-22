/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 23:05:00 by abarbour          #+#    #+#             */
/*   Updated: 2021/01/23 17:20:07 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cd_change_env(char *str, char ***envp)
{
	char	*buf;

	if (!(buf = malloc(MAXPATHLEN + 1)))
		return (-1);
	buf[MAXPATHLEN] = 0;
	if (!getcwd(buf, MAXPATHLEN))
	{
		free(buf);
		return (-1);
	}
	buf = ft_strjoinfree(str, buf, 2);
	add_var_to_env(buf, envp);
	free(buf);
	return (0);
}

char	*get_env_val(char *str, char **envp)
{
	int	c;
	int	i;

	c = 0;
	while (envp[c] != NULL && ft_strncmp(envp[c],
			str, envp_len(envp[c], str)))
		c++;
	i = 0;
	while (envp[c] && envp[c][i] != '=')
		i++;
	if (envp[c])
		return (envp[c] + i + 1);
	return ("");
}

int		cd_change_envpwd(char *str, char ***envp)
{
	char	*buf;

	if (!(buf = malloc(MAXPATHLEN + 1)))
		return (-1);
	buf[MAXPATHLEN] = 0;
	buf = get_env_val("PWD", *envp);
	buf = ft_strjoin(str, buf);
	add_var_to_env(buf, envp);
	free(buf);
	return (0);
}

int		ft_cd(char **args, char ***envp)
{
	if (cd_change_envpwd("OLDPWD=", envp) == -1)
		return (-1);
	if (chdir(args[1]))
		return (-1);
	if (cd_change_env("PWD=", envp) == -1)
		return (-1);
	return (0);
}
