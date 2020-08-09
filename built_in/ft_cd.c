/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 23:05:00 by abarbour          #+#    #+#             */
/*   Updated: 2020/08/09 21:49:42 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_cd(char *path, char **args, char **envp)
{
	char	*buf;
	int		i;

	if (!(buf = malloc(MAXPATHLEN + 1)))
		return (-1);
	buf[MAXPATHLEN] = 0;
	if (!getcwd(buf, MAXPATHLEN))
	{
		free(buf);
		return (-1);
	}
	buf = ft_strjoin("OLDPWD=", buf);
	add_var_to_env(buf, &envp);
	i = -1;
	if (chdir(args[1]))
		return (-1);
	if (!getcwd(buf, MAXPATHLEN))
	{
		free(buf);
		return (-1);
	}
	buf = ft_strjoinfree("PWD=", buf, 2);
	add_var_to_env(buf, &envp);
	free(buf);
	return (0);
}
