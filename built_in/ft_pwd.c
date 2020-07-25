/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:48:49 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/25 23:30:15 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_pwd(char *path, char **args, char **envp)
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
	i = -1;
	while (buf[++i])
		write(1, buf + i, 1);
	write(1, "\n", 1);
	free(buf);
	exit(0);
}
