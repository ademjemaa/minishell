/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 23:05:00 by abarbour          #+#    #+#             */
/*   Updated: 2020/08/10 22:29:37 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cd_change_env(char *str, char **envp)
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
	update_env(buf, envp, -1);
	free(buf);
	return (0);
}

int		ft_cd(char *path, char **args, char **envp)
{
	if (cd_change_env("OLDPWD=", envp) == -1)
		return (-1);
	if (chdir(args[1]))
		return (-1);
	if (cd_change_env("PWD=", envp) == -1)
		return (-1);
	return (0);
}
