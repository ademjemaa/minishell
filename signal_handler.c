/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 21:14:06 by abarbour          #+#    #+#             */
/*   Updated: 2020/08/07 23:10:41 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	int_handler(int signum)
{
	write(1, "\nkembyalet$ ", 13);
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
