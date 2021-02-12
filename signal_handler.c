/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 21:14:06 by abarbour          #+#    #+#             */
/*   Updated: 2020/08/09 18:07:47 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_length(char *line)
{
	t_check c;

	init_struct(&c);
	while (line[c.i])
	{
		while (line[c.i] == '\\' && c.one == 0)
			c.i = c.i + 2;
		if (line[c.i] == '\'' && c.two == 0)
			c.one = !c.one;
		if (line[c.i] == '\"' && c.one == 0)
			c.two = !c.two;
		if ((line[c.i] == '|' || line[c.i] == ';') &&
			line[c.i + 1] != '\0' && c.one == 0 && c.two == 0)
			return (c.i);
		c.i++;
	}
	return (c.i);
}

void	int_handler(int signum)
{
	if (g_childs == 0)
		write(1, "\nkembyalet$ ", 13);
	else
		write(1, "\n", 1);
	g_exit_code = 1;
}

void	quit_handler(int signum)
{
	return ;
}

void	catch_signals(void)
{
	signal(SIGINT, &int_handler);
	signal(SIGQUIT, &quit_handler);
}
